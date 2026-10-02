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
	uint64_t carry = 0;
    	uint64_t wrk[S + 1];
    	uint32_t *al0 = (uint32_t *)in0, *al1 = (uint32_t *)in1 , *alw = (uint32_t *)wrk;

	memset(wrk, 0, BYTES + sizeof(uint64_t));

	/* For i-th entry in al0 (left operand) */
	for (i = 0; i < S*2; i++) {
		/* For each bit */
		for (k = 0; k < 32; k++) {
			/* If there is a postive bit at this location */
			if ((al0[i] << (31-k)) >> 31) {
				/* For j-th entry in al1 (right operand), starting from the left-most term */
				/* Basically, shift the right operand over k bits */
				for (j = (S*2)-1; j < S*2; j--) {
					/* Make sure we don't go out of the array bounds */	
					if (i+j < (S*2)+1) {
						/* Take the overflow of multiplication and add it to the previous slot */
						alw[i+j+1] = alw[i+j+1] | (uint32_t)(((uint64_t)al1[j] << k) >> 32);
						/* Shift the current term and add it to the working variable */
						alw[i+j] = (al1[j] << k);
					}
				}
				/* Add that shifted number back into the output */
				carry = bigadd(wrk, out, out);
				/* Reset the working variable */
				memset(wrk, 0, BYTES + sizeof(uint64_t));
			}
		}
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
	
	generateRandom2048Bit(in0);
	generateRandom2048Bit(in1);

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
	seebinary(in0);
	fprintf(stderr, "Second Multiplication Input: \n");
	seebig(in1);
	seebinary(in1);
	fprintf(stderr, "Carry: \n");
	fprintf(stderr, "%lu\n", bigmul(in0, in1, out));
	fprintf(stderr, "Product: \n");
	seebig(out);
	seebinary(out);

	return 0;
}
