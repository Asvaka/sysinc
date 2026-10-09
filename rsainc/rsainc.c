#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint64_t modexp(uint64_t m, uint64_t e, uint64_t n) {
	if (e == 0) {
		return 1;
	}
	if (e == 1) {
		return m % n;
	}
	if (e % 2) {
		return (m * modexp(((m%n)*(m%n)) % n, e/2, n)) % n;
	}
	return modexp(((m%n)*(m%n)) % n, e/2, n) % n;
}

int main(int argc, char**argv) {
	FILE *fp;
	FILE *out;
	
	uint64_t n, d, e, tmp = 0;
	uint8_t bytes[4];

	if (argc != 4) {
		fprintf(stderr, "Error: incorrect number of arguments passed: %d. Pass exactly three arguments.\n", argc-1);
		exit(1);
	}
	if (argv[1][0] == '-') {
		if (argv[1][1] == 'e') {
			fp = fopen("unsafe.pub", "r");
			d = fscanf(fp, "-----BEGIN UNSAFE PUBLIC KEY-----\n%lx\n%lx\n-----END UNSAFE PUBLIC KEY-----\n", &n, &e);	
		}
		else if (argv[1][1] == 'd') {
			fp = fopen("unsafe.bad", "r");
			d = fscanf(fp, "-----BEGIN UNSAFE PRIVATE KEY-----\n%lx\n%lx\n%lx\n-----END UNSAFE PRIVATE KEY-----\n", &n, &d, &e);
		}
	}
	else {
		fprintf(stderr, "Error: no option command given.\n");
		exit(1);
	}
	
	fp = fopen(argv[2], "rb");
	out = fopen(argv[3], "wb");

	if (fp == NULL) {
		fprintf(stderr, "Error: file \"%s\" could not be opened.\n", argv[2]);
		exit(1);
	}

	d = fread(bytes, 1, 4, fp);
	while (d < 4) {
		bytes[d] = 0;
		d++;
	}

	memcpy(&tmp, bytes, 4);
	tmp = modexp(tmp, e, n);

	fwrite(&tmp, d, 1, out);
	
	return 0;
}
