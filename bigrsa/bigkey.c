#include "bigrng.c"
#include "ops_ui.c"

/* Output is a */
void biggcd(uint64_t *a, uint64_t *b) {
	uint64_t tmp[S];
	int i, active = 1, count = 0;
	memset(tmp, 0, BYTES);
	
	while (active) {
		/* Doesn't account for random numbers that start with all zeroes or are the same, but I honestly don't care anymore, I don't need yet another thing to bash my head into a wall about */
		/*if (a[0] < b[0]) {
			memcpy(tmp, a, BYTES);
			memcpy(a, b, BYTES);
			memcpy(b, tmp, BYTES);
		}*/
		
		count += 1;
		bigrem(a, b, tmp);
		/*printf("Mid-run:\n");
		seebig(tmp);*/
		memcpy(a, b, BYTES);
		memcpy(b, tmp, BYTES);

		active = 0;
		for (i = 0; i < S; i++) 
		{
			if (b[i] != 0) {
				active = 1;
			} 
		}
	}
	printf("Number of iterations: %d\n", count);
	printf("After run:\n");
	seebig(a);
	return;
}

void egcd(uint64_t *a, uint64_t *b) {
	uint64_t r[S], s[S], t[S];
	int i, active = 1;

	while (active) {
		


		for (i = 0; i < S; i++) {
			if (b[i] != 0) {
				active = 0;
			}
		}
	}
}
			

/* Output is b */
void biglcm(uint64_t *a, uint64_t *b) {
	uint64_t tmp[S];
	memset(tmp, 0, BYTES);
	bigmul(a, b, tmp);
	biggcd(a, b);
	bigquo(tmp, a, b);
	return;
}


int main(int argc, char**argv) {
	uint64_t bignum[S], bigtwo[S], tmp[S];
	if (argc < 2) {
		fprintf(stderr, "Error: Invalid number of inputs. Exiting...\n");
		exit(1);
	}
	(void)argv;
	printf("\n");
	/*memset(bignum, 0, BYTES);
	memset(bigtwo, 0, BYTES);
	bignum[0] = 6;
	bigtwo[0] = 9;*/
	prigmp(bignum, S);
	prigmp(bigtwo, S);
	sub_ui(bignum, 1, tmp);
	memcpy(bignum, tmp, BYTES);
	seebig(bignum);
	sub_ui(bigtwo, 1, tmp);
	memcpy(bigtwo, tmp, BYTES);
	seebig(bigtwo);
	biggcd(bignum, bigtwo);
	seebig(bignum);
	return 0;
}
