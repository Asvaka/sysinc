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
    	uint64_t wrk[S*2 + 1];
    	uint32_t *al0 = (uint32_t *)in0, *al1 = (uint32_t *)in1 , *alw = (uint32_t *)wrk, *alo = (uint32_t *)out;

	(void)alw;
	(void)carry;

	/* Goal is to simulate bit shifting entire right operand every time we see a "yes" binary with i */
	for (k = 0; k < 4; k++) {
		/*fprintf(stderr, "Testing %lu-th: %x\n", k, al1[k]);*/
		/*fprintf(stderr, "Testing value: %x\n", al1[k]);*/
		for (j = 0; j < 4; j++) {
			tmp = 0;
			for (i = 0; i < 32; i++) {
				if((al0[j] << (31-i)) >> 31) {
					/* Need to watch for overflow in the output as well */
					/* Two types of overflow: Operand Multiplication overflow, and Carry Addition overflow */
					tmp += ((uint64_t)al1[k] << i);
					/* Operand Multiplication is taken care of here with the shifting back and forth */
					/* Carry Addition still needs to be adressed. Check if shifted operand + tmp goes over?*/
					/*fprintf(stderr, "TMP: %lx\n", tmp);*/
					/*if(j+k == 2){
					fprintf(stderr, "Hit on operand %lu: shifting %lx by %lu bits, to add %lx on space %lu, with current tmp %lx\n", j, (uint64_t)al1[k], i, (uint64_t)al1[k] << i, j+k, tmp);
					}*/
				}
			}
			carry = (alo[j+k] + (uint32_t)tmp) < alo[j+k];
			alo[j+k] += (uint32_t)tmp;
			alo[j+k+1] += carry + (uint32_t)(tmp >> 32);
			/*fprintf(stderr, "TMP: %lb\nTMP Shortened: %b\nTMP Shortened & Shifted: %b\n", tmp, (uint32_t)tmp, (uint32_t)(tmp >> 32));*/
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
	fprintf(stderr, "%064lb", a[0]);
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
	for (i = 0; i < S/2; i++) {
		in0[i] = (i+1)*(16*100000000);
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
