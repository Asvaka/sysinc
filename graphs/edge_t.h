#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct edge_struct *edge_t;

edge_t edge_new();

void edge_free(edge_t e);
