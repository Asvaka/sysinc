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

int main() {
	uint64_t min[S], sub[S], dif[S];
	uint64_t in0[S], in1[S], sum[S];
	size_t i;
	memset(min, 0, BYTES);
	memset(sub, 0, BYTES);
	memset(in0, 0, BYTES);
	memset(in1, 0, BYTES);
	for (i = 0; i < S; i++) {
		min[i] = i*3;
		sub[i] = i*2;
	}
	for (i = 0; i < S; i++) {
		in0[i] = i*1000 << 48;
		in1[i] = i*600 << 48;
	}
	fprintf(stderr, "First Subtraction Input: \n");
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
	seebig(sum);

	return 0;
}
