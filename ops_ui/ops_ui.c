#include "ops_ui.h"
#include <string.h>

uint64_t add_ui(uint64_t *big, uint64_t lil, uint64_t *out) {
	uint64_t tmp[64];
	memset(tmp, 0, BYTES);
	tmp[0] = lil;
	return bigadd(big, tmp, out);
}

uint64_t sub_ui(uint64_t *big, uint64_t lil, uint64_t *out) {
	uint64_t tmp[64];
	memset(tmp, 0, BYTES);
	tmp[0] = lil;
	return bigsub(big, tmp, out);
}

uint64_t mul_ui(uint64_t *big, uint64_t lil, uint64_t *out) {
	uint64_t tmp[64];
	memset(tmp, 0, BYTES);
	tmp[0] = lil;
	return bigmul(big, tmp, out);
}
uint64_t quo_ui(uint64_t *big, uint64_t lil, uint64_t *out) {
	uint64_t tmp[64];
	memset(tmp, 0, BYTES);
	tmp[0] = lil;
	return bigquo(big, tmp, out);
}

uint64_t rem_ui(uint64_t *big, uint64_t lil, uint64_t *out) {
	uint64_t tmp[64];
	memset(tmp, 0, BYTES);
	tmp[0] = lil;
	return bigrem(big, tmp, out);
}

