#include <stdio.h>

int printb(int n) {
	unsigned int c = n;
	int i;
	int j;
	int k = (sizeof(n) * 8) - 1;

	for (j = sizeof(n) - 1; j >= 0; j--) {
		if (!(c >> (j*8))) {
			k -= 8;	
		}
	}

	for (i = k; i >= 0; i--) {
		int mask = 1 << i;

		printf("%u", (c & mask) >> i);
	}

	return 0;
}

