#include "edge_t.h"

struct edge_struct {
	char src[3];
	char dst[3];
	uint32_t mi;
	uint32_t name; /* interstate # (not sure how this is useful, probably won't use) */
};

edge_t edge_new(char src[3], char dst[3], uint32_t mi, uint32_t name) {
	edge_t e = malloc(sizeof(struct edge_struct));
	memcpy(e->src, src, 1);
	memcpy(e->dst, dst, 1);
	e->mi = mi;
	e->name = name;
}

void edge_free(edge_t e) {
	free(e);
}
