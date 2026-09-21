#include <stdio.h>
#include <stdint.h>

/*uint32_t my_htonl(uint32_t n) {
	uint8_t swap, *alias = (uint8_t *)&n;
	size_t index;
	swap = alias[0];
	alias[0] = alias[3];
	alias[3] = swap;
	swap = alias[1];
	alias[1] = alias[2];
	alias[2] = swap;
	return n;
}*/

uint64_t htonll(uint64_t n) {
	uint8_t swap, *alias = (uint8_t *)&n;
	size_t index;
	for (index = 0; index < sizeof(n)/2; index++) {
		swap = alias[index];
		alias[index] = alias[sizeof(n)-index-1];
		alias[sizeof(n)-index-1] = swap;
	}
	return n;
}

int main() {
	uint64_t test = 0x123456789ABCDEF;
	printf("%016lX\n%016lX\n",
			test,
			htonll(test)
		);
	return 0;
}
