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
	size_t i, j;
	uint64_t carry = 0, true_carry = 0, tmp;
	(void)tmp;	
	/* For every bit in each 64-bit int */
	for (j = 0; j < 64; j++) {
		/* For every 64-bit int passed */
		for (i = 0; i < S; i++) {
			/* Get the j-th binary digit of in0[i] */
			if ((in0[i] << (63-j)) >> 63) { 
				tmp = in1[i] << j;

				out[i] += carry + (in1[i] << j);
				carry = in1[i] >> (64-j);
			}
		}
		true_carry += carry;
		carry = 0;

	}

	return carry;
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
	for (i = S-1; i > 0; i--) {
		fprintf(stderr, "%016lx ", a[i]);
		if ((i % 8 == 0 && i)) {
			fprintf(stderr, "\n");
		}
	}
	fprintf(stderr, "\n\n");
	return;
}

