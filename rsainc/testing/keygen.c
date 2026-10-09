#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


uint16_t is_prime(uint16_t n) {
	uint16_t i;
	
	for (i = 2; i < ((n/2)+1); i++) {
		if (!(n % i)) {
			return 0;
		}
	}


	return 1;
}

uint16_t sixkp1(uint16_t k) {
	size_t candidate = 6 * k + 1;
	while (!is_prime(candidate)) {
		candidate += 6;
	}
	return candidate;
}

uint64_t gcd(uint64_t a, uint64_t b) {
	uint64_t tmp = 0;
	while (b) {
		tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
	return (a * b) / gcd(a, b);
}

uint16_t generateRandom16Bit() {
	FILE *fp = fopen("/dev/urandom", "r");
	uint16_t rd_num;
	size_t l;

	/* Now returns 16 bit int */
	l = fread(&rd_num, 2, 1, fp);
	(void)l;
	fclose(fp);

	rd_num = rd_num % (5460 - 10000 - 1) + 5460;

	return rd_num;
}

uint64_t find_d(uint64_t e, uint64_t lmdb) {
	uint64_t d = 1;
	while (1 != ((d * e) % lmdb)) {
		d += 1;
	}
	return d;
}

int main() {
	size_t p = sixkp1((uint32_t)generateRandom16Bit()), q = sixkp1((uint32_t)generateRandom16Bit());

	char* hd = "-----BEGIN";
	char* ft = "-----END";
	char* tl1 = " UNSAFE PRIVATE KEY-----\n";
	char* tl2 = " UNSAFE PUBLIC KEY-----\n";

	FILE *fp1 = fopen("unsafe.bad", "w");
	FILE *fp2 = fopen("unsafe.pub", "w");

	size_t n = p * q;
	size_t e = 65537;
	size_t lmdb = lcm(p - 1, q - 1);
	size_t d = find_d(e, lmdb);
	while (d > lmdb) {
		d += lcm(p - 1, q - 1);
	}

	fprintf(fp1, "%s%s%lx\n%lx\n%lx\n%s%s", hd, tl1, n, e, d, ft, tl1);
	fprintf(fp2, "%s%s%lx\n%lx\n%s%s", hd, tl2, n, e, ft, tl2);
	
	fclose(fp1);
	fclose(fp2);

	return 0;
}
