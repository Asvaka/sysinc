#include <stdio.h>
#include <math.h>

int printb(char n) {
	int c = n;

	/*int tracker = 255;*/
	int i;
	for (i = 8; i > 0; i--) {
		int new = pow(2, i - 1);
		if (c >= new) {
			printf("1");
			c = c - new;
		} else {
			printf("0");
		}
	}

	printf("\n");

	return 0;
}

int main(int argc, char **argv) {
	int input_len = 0;
	(void)argc;
	/*printf("Testing Input");
	printf("%s", argv[1]);*/
	while(argv[1][input_len] != '\0') {
		printb(argv[1][input_len]);
		input_len++;
	}
	/*printb('a');*/
	return 0;
}
