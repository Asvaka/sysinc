#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t htonl(uint32_t n) {
	uint8_t swap, *alias = (uint8_t *)&n;
	swap = alias[0];
	alias[0] = alias[3];
	alias[3] = swap;
	swap = alias[1];
	alias[1] = alias[2];
	alias[2] = swap;
	return n;
}

int encode(uint32_t in) {
	int out = (int)(in % 85);
	int i;
	uint32_t tmp = in;
	int outs[5];
	int stop = 0;
	(void)stop;

	for (i = 0; i < 5; i++) {
		/*printf("Out: %d\n", out);*/
		out += 33;
		outs[i] = out;
		if (tmp < 85) {
			stop = i;
			break;
		}
		tmp = tmp / 85;
		out = (int)(tmp % 85);
	}
	printf("<~");
	for (i = stop; i > -1; i--) {
		printf("%c", outs[i]);
	}
	printf("~>");

	return 0;
}

int main(int argc, char**argv) {
	FILE* fp;
	uint32_t bytes = 0;
	uint8_t *alias = (uint8_t *)&bytes;
	size_t l;

	(void)l;
	(void)alias;

	if (argc != 2) {
		fprintf(stderr, "Error: Please pass exactly one argument. Exiting...\n");
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: Couldn't open file at %s. Exiting...\n", argv[1]);
		exit(1);
	}

	l = fread(&bytes, 4, 1, fp);
	/*printf("Check: %u\n", bytes);
	printf("Bytes pre-htonl: %x\n", bytes);*/
	bytes = htonl(bytes);

	encode(bytes);
	return 0;
}	
