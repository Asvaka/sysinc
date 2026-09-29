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
	uint64_t carry = 0, true_carry = 0, tmp;
	(void)tmp;
	(void)carry;
	(void)true_carry;
	/* For each 64-bit int in the right operand */
	for (k = 2; k < 3; k++) {
		/*fprintf(stderr, "Desired value: %x\n", 0x6 * 0xa);*/
		/* For every 64-bit int in the left operand */
		for (j = 0; j < S; j++) {
			/* For every bit in each 64-bit int */
			for (i = 0; i < 64; i++) {
				/* Get the i-th binary digit of in0[j] */
				if ((in0[j] << (63-i)) >> 63) {
					out[j] += (in1[k] << i);
					/*fprintf(stderr, "Hit on operand %lu: shifting %lx by %lu, to add %lx\n", j, in1[k], i, in1[k] << i);*/
				}
			}
		}
	}

	return 0;
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

int main() {
	uint64_t min[S], sub[S], dif[S];
	uint64_t in0[S], in1[S], sum[S], out[S];
	size_t i;
	memset(min, 0, BYTES);
	memset(sub, 0, BYTES);
	memset(in0, 0, BYTES);
	memset(in1, 0, BYTES);
	memset(out, 0, BYTES);
	for (i = 0; i < S; i++) {
		min[i] = (i+1)*3;
		sub[i] = (i+1)*2;
	}
	for (i = 0; i < S; i++) {
		in0[i] = (i+1)*3;
		in1[i] = (i+1)*5;
	}

	(void)min;
	(void)sub;
	(void)dif;
	(void)sum;

	/*fprintf(stderr, "First Subtraction Input: \n");
	seebig(min);
	fprintf(stderr, "Second Subtraction Input: \n");
	seebig(sub);
	fprintf(stderr, "Carry: \n");
	fprintf(stderr, "%lu\n", bigsub(min, sub, dif));
	fprintf(stderr, "Difference: \n");
	seebig(dif);

	fprintf(stderr, "First Addition Input: \n");
	seebig(in0);
	fprintf(stderr, "Second Addition Input: \n");
	seebig(in1);
	fprintf(stderr, "Carry: \n");
	fprintf(stderr, "%lu\n", bigadd(in0, in1, sum));
	fprintf(stderr, "Sum: \n");
	seebig(sum);*/

	fprintf(stderr, "First Multiplication Input: \n");
	seebig(in0);
	fprintf(stderr, "Second Multiplication Input: \n");
	seebig(in1);
	fprintf(stderr, "Carry: \n");
	fprintf(stderr, "%lu\n", bigmul(in0, in1, out));
	fprintf(stderr, "Product: \n");
	seebig(out);

	return 0;
}
