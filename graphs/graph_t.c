#include "graph_t.h"

struct graph_struct {
	list_t edges;
	list_t nodes;
};

graph_t graph_new() {
	graph_t g = malloc(sizeof(struct graph_struct));
	g->edges = list_new();
	g->nodes = list_new();

	return g;
}

void graph_free(graph_t g) {
	list_map_void(g->edges, (void (*)(void*))edge_free);
	list_free(g->edges);
	list_map_void(g->nodes, (void (*)(void*))node_free);
	list_free(g->nodes);
	free(g);
}

int main() {
	graph_t g = graph_new();

	list_append(g->edges, edge_new("SEA", "PDX", 174, 5));

	graph_free(g);
	return 0;
}
