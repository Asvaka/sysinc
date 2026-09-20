#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	uint8_t bytes[64];
	size_t l = 64;	

	size_t i;

	FILE *fp;

	if (argc < 1) {
		fprintf(stderr, "Error: no filenames provided. Exiting...\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	
	if (fp == NULL) {
		fprintf(stderr, "Error: fopen fails on f_name \"%s\", exiting...\n", argv[1]);
		exit(1);
	}	

	while (l == 64) {
		l = fread(bytes, 1, 64, fp);
		
		for (i = 0; i < l; i++) {
			printf("%02x", bytes[i]);
			if ((i+1) % 16 == 0) {
				printf("\n");
			}
			else if ((i+1) % 4 == 0) {
				printf(" ");
			}
		}

		printf("\n");
	}

	if (fclose(fp) == EOF) {
		fprintf(stderr, "Error: fclose fails on f_name \"%s\", exiting...\n", argv[1]);
	}

	return 0;
}
