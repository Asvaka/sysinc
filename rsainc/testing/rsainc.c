#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t modexp(uint64_t m, uint64_t e, uint64_t n) {
	if (e == 0) {
		return 1;
	}
	if (e == 1) {
		return m % n;
	}
	if (e % 2) {
		return (m * modexp(m*m % n, e/2, n)) % n;
	}
	return modexp(m*m % n, e/2, n) % n;
}

int main(int argc, char**argv) {
	FILE *fp;
	FILE *out;
	
	uint64_t n, d, e, i, tmp;
	uint8_t bytes[4];
	(void)bytes;
	(void)out;

	if (argc != 4) {
		fprintf(stderr, "Error: incorrect number of arguments passed: %d. Pass exactly three arguments.\n", argc-1);
	}
	if (argv[1][0] == 'e') {
		fp = fopen("unsafe.pub", "r");
		d = fscanf(fp, "-----BEGIN UNSAFE PUBLIC KEY-----\n%lx\n%lx\n-----END UNSAFE PUBLIC KEY-----\n", &n, &e);	
	}
	else if (argv[1][0] == 'd') {
		fp = fopen("unsafe.bad", "r");
		d = fscanf(fp, "-----BEGIN UNSAFE PRIVATE KEY-----\n%lx\n%lx\n%lx\n-----END UNSAFE PRIVATE KEY-----\n", &n, &d, &e);
	}
	else {
		fprintf(stderr, "Error: no option command given.\n");
		exit(1);
	}
	
	/*printf("Input: 99\n");
	printf("Output: %lu\n", modexp(99, e, n)); */

	
	fp = fopen(argv[2], "r");
	out = fopen(argv[3], "w");

	if (fp == NULL) {
		fprintf(stderr, "Error: file \"%s\" could not be opened.\n", argv[2]);
		exit(1);
	}

	d = fread(bytes, 1, 4, fp);
	while (d < 4) {
		bytes[d] = 0;
		d++;
	}

	tmp = modexp(bytes[0], e, n);
	/*tmp = modexp((uint64_t)bytes, e, n);
	bytes = (uint8_t*)tmp;
	fprintf(stderr, "Byte: %u\n", bytes[i]);*/
	for (i = 0; i < d; i++) {
		printf("%u\n", (uint8_t)((tmp << (63 - i*8)) >> (63 - i*8)));
		fprintf(out, "%c", (uint8_t)((tmp << (63 - i*8)) >> (63 - i*8)));
	}
	
	/*printf("Input: %lx\n", (uint64_t)bytes);

	printf("Output: %lx\n", modexp((uint64_t)bytes, e, n));*/
	/*printf("Input: %s\n", argv[2]);
	printf("Output: %lx\n", modexp((uint64_t)argv[2], e, n));*/
	
	return 0;
}
