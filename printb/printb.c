#include <stdio.h>

int printb(char n) {
	int c = n;
	int i;

	for (i = 7; i >= 0; i--) {
		int mask = 1 << i;

		printf("%d", (c & mask) >> i);
	}

	return 0;
}
