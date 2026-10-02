/* 4096_t.c */

#include "4096_t.h"

uint64_t bigsub(uint64_t *min, uint64_t *sub, uint64_t *dif) {
	size_t i;
	uint64_t carry = 0, tmp;
	for (i = 0; i < S; i++) {
		tmp = min[i] - sub[i] - carry;
		carry = min[i] < sub[i];
		dif[i] = tmp;
	}
	return carry;
}

uint64_t bigadd(uint64_t *in0, uint64_t *in1, uint64_t *sum) {
	size_t i;
	uint64_t carry = 0, tmp;
	for (i = 0; i < S; i++) {
		tmp = in0[i] + in1[i] + carry;
		/* I wonder if there is some way to do this with bit shift? */
		carry = tmp < in1[i] || tmp < in0[i];

		sum[i] = tmp;
	}
	return carry;
}

uint64_t bigmul(uint64_t *in0, uint64_t *in1, uint64_t *out) {
	size_t i, j, k;
	uint64_t carry = 0, tmp = 0;
    	uint64_t wrk[S + 1];
    	uint32_t *al0 = (uint32_t *)in0, *al1 = (uint32_t *)in1 , *alw = (uint32_t *)wrk, *alo = (uint32_t *)out;

	(void)alw;
	(void)alo;
	(void)carry;

	memset(wrk, 0, BYTES + sizeof(uint64_t));

	/* For i-th entry in al0 (left operand) */
	for (i = 0; i < S*2; i++) {
		/* For each bit */
		for (k = 0; k < 32; k++) {
			if ((al0[i] << (31-k)) >> 31) {
				/* For j-th entry in al1 (right operand) */
				for (j = (S*2)-1; j < S*2; j--) {
					/* Shift the number as a whole, then add it to an accumulator */
					/* If doesn't work, use polynomial method */
					/* Use 128-bit at first as testing it */
					/* Might have 128-bit c type support for testing */


					/* Use wrk to capture the overflow from 32-bit addition */
					if (i+j < (S*2)+1) {
						alw[i+j+1] = alw[i+j+1] | (uint32_t)(((uint64_t)al1[j] << k) >> 32);
						alw[i+j] = (al1[j] << k);
					}
				}
				/*fprintf(stderr, "i, k: %lu, %lu\n", i, k);
				fprintf(stderr, "alw: \n");
				for (j = (S*2)-1; j < (S*2); j--) {
					fprintf(stderr, "%032b", alw[j]);
					if ((j % 8 == 0 && j)) {
						fprintf(stderr, "\n");
					}
				}
				fprintf(stderr, "\n");
				fprintf(stderr, "wrk: \n");
				for (j = S-1; j < S; j--) {
					fprintf(stderr, "%064lb", wrk[j]);
					if ((j % 8 == 0 && j)) {
						fprintf(stderr, "\n");
					}
				}
				fprintf(stderr, "\n\n");*/
				carry = bigadd(wrk, out, out);
				memset(wrk, 0, BYTES + sizeof(uint64_t));
			}
		}
	}
	
	return (tmp >> 32);
}

uint64_t bigquo(uint64_t *num, uint64_t *den, uint64_t *quo) {
	(void)num;
	(void)den;
	(void)quo;
	return 0;
}

uint64_t bigrem(uint64_t *num, uint64_t *den, uint64_t *rem) {
	(void)num;
	(void)den;
	(void)rem;
	return 0;
}

void seebig(uint64_t *a) {
	size_t i;
	for (i = S-1; i < S; i--) {
		fprintf(stderr, "%016lx ", a[i]);
		if ((i % 8 == 0 && i)) {
			fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "\n\n");
	return;
}

void seebinary(uint64_t *a) {
	size_t i;
	for (i = S-1; i < S; i--) {
		fprintf(stderr, "%064lb", a[i]);
		if ((i % 8 == 0 && i)) {
			fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "\n\n");
	return;
}

uint64_t generateRandom2048Bit(uint64_t *s) {
	FILE *fp = fopen("/dev/urandom", "r");
	size_t l;

	l = fread(s, 8, S/2, fp);
	fclose(fp);

	return l;
}
