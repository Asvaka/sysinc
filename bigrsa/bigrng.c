#include "biggmp.c"

void prigmp(uint64_t *big, uint8_t words) {
	/* populate from buffer */
	mpz_t m;
	FILE *fp = fopen("/dev/random", "r");
	int l;
	(void)l;
	memset(big, 0, BYTES);
	l=fread(big, sizeof(uint64_t), words, fp);
	fclose(fp);
	mpz_init(m);
	mpz_import(m, S, -1, sizeof(uint64_t), 0, 0, big);
	mpz_nextprime(m, m);
	mpz_export(big, NULL, -1, sizeof(uint64_t), 0, 0, m);
	mpz_clear(m);
	return;
}

int main() {
	uint64_t bignum[S];
	prigmp(bignum, S);
	seebig(bignum);
	return 0;
}
