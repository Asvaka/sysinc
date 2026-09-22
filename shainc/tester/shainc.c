#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rounds.c"

#define CHOICE(e, f, g) (((e)&(f))|((~(e))&(g)))
#define MEDIAN(e, f, g) ((((e)|(f))&(g))|(((f)|(g))&(e)))
#define ROTATE(e, f) (((e)>>(f))|((e)<<((sizeof(e)*8)-f)))
#define SIG0(m) ((ROTATE(m,2)^ROTATE(m,13))^ROTATE(m,22))
#define SIG1(m) ((ROTATE(m,6)^ROTATE(m,11))^ROTATE(m,25))
#define LSIG0(m) ((ROTATE(m,7)^ROTATE(m,18))^(m>>3))
#define LSIG1(m) ((ROTATE(m,17)^ROTATE(m,19))^(m>>10))

int main(int argc, char** argv) {
    uint8_t bytes[64];
    size_t l = 64;
    size_t length = 0;

    size_t i;

    FILE *fp;

    /* Message Schedule Array */
    uint32_t msa[64];
    /* Hash Tracker */
    uint32_t hash[8] = {
        0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,
        0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19
    };
    /* Working Variables */
    uint32_t a, b, c, d, e, f, g, h;

    uint32_t temp1, temp2;

    int final_exists = 0;

    if (argc < 1) {
        fprintf(stderr, "Error: no filenames provided. Exiting...\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "Error: fopen fails on f_name \"%s\", exiting...\n", argv[1]);
        exit(1);
    }

    /* While the last processed chunk is a full 512 bits */
    while (l == 64) {
        l = fread(bytes, 1, 64, fp);
        length += l << 3;

        /* Pre-Processing (Padding) */
        if (l != 64) {
            bytes[l] = 1 << 7;
            if (64-(l+1) > 8) {
                for (i = l+1; i < 64-8; i++) {
                    bytes[i] = 0;
                }
                bytes[56] = (uint8_t)(length >> 56);
                bytes[57] = (uint8_t)(length >> 48);
                bytes[58] = (uint8_t)(length >> 40);
                bytes[59] = (uint8_t)(length >> 32);
                bytes[60] = (uint8_t)(length >> 24);
                bytes[61] = (uint8_t)(length >> 16);
                bytes[62] = (uint8_t)(length >> 8);
                bytes[63] = (uint8_t)(length);
            }
            else {
                /* If there's not enough room to fit length in the end of the array, add it later */
                final_exists = 1;

                for (i = l+1; i < 64; i++) {
                    bytes[i] = 0;
                }
            }
        }

        /* Set Message Schedule Array */
        for (i = 0; i < 16; i++) {
            msa[i] = (bytes[i*4] << 24) | (bytes[(i*4)+1] << 16) | (bytes[(i*4)+2] << 8) | bytes[(i*4)+3];
        }

        for (i = 16; i < 64; i++) {
            msa[i] = LSIG1(msa[i-2]) + msa[i-7] + LSIG0(msa[i-15]) + msa[i-16];
        }

        a = hash[0];
        b = hash[1];
        c = hash[2];
        d = hash[3];
        e = hash[4];
        f = hash[5];
        g = hash[6];
        h = hash[7];

        /* Main Loop */
        for (i = 0; i < 64; i++) {
            temp1 = h + SIG1(e) + CHOICE(e,f,g) + k[i] + msa[i];
            temp2 = SIG0(a) + MEDIAN(a,b,c);

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hash[0] = a + hash[0];
        hash[1] = b + hash[1];
        hash[2] = c + hash[2];
        hash[3] = d + hash[3];
        hash[4] = e + hash[4];
        hash[5] = f + hash[5];
        hash[6] = g + hash[6];
        hash[7] = h + hash[7];
    }

    if (final_exists == 1) {

        for (i = 0; i < 64-8; i++) {
            bytes[i] = 0;
        }
        bytes[56] = (uint8_t)(length >> 56);
        bytes[57] = (uint8_t)(length >> 48);
        bytes[58] = (uint8_t)(length >> 40);
        bytes[59] = (uint8_t)(length >> 32);
        bytes[60] = (uint8_t)(length >> 24);
        bytes[61] = (uint8_t)(length >> 16);
        bytes[62] = (uint8_t)(length >> 8);
        bytes[63] = (uint8_t)(length);


        /* Set Message Schedule Array */
        for (i = 0; i < 16; i++) {
            msa[i] = (bytes[i*4] << 24) | (bytes[(i*4)+1] << 16) | (bytes[(i*4)+2] << 8) | bytes[(i*4)+3];
        }

        for (i = 16; i < 64; i++) {
            msa[i] = LSIG1(msa[i-2]) + msa[i-7] + LSIG0(msa[i-15]) + msa[i-16];
        }


        a = hash[0];
        b = hash[1];
        c = hash[2];
        d = hash[3];
        e = hash[4];
        f = hash[5];
        g = hash[6];
        h = hash[7];

        /* Main Loop */
        for (i = 0; i < 64; i++) {
            temp1 = h + SIG1(e) + CHOICE(e,f,g) + k[i] + msa[i];
            temp2 = SIG0(a) + MEDIAN(a,b,c);

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        hash[0] = a + hash[0];
        hash[1] = b + hash[1];
        hash[2] = c + hash[2];
        hash[3] = d + hash[3];
        hash[4] = e + hash[4];
        hash[5] = f + hash[5];
        hash[6] = g + hash[6];
	hash[7] = h + hash[7];
    }

    for (i = 0; i < 8; i++) {
        printf("%08x", hash[i]);
    }

    printf("  %s\n", argv[1]);
	
    if (fclose(fp) == EOF) {
        fprintf(stderr, "Error: fclose fails on f_name \"%s\", exiting...\n", argv[1]);
    }

    return 0;
}
