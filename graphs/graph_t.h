#include <stdio.h>
#include <stdint.h>

#include "list_t.h"
#include "edge_t.h"
#include "node_t.h"

typedef struct graph_struct *graph_t;

graph_t graph_new();

void graph_free();

void graph_print(graph_t g);

void graph_add_edge(edge_t e);

void graph_add_node(node_t n);
