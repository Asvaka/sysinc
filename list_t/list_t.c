#include "list_t.h"

struct list_struct {
	size_t list_size;
	size_t arr_size;
	void **list_arr;
};

list_t list_new() {
	list_t l = malloc(sizeof(struct list_struct));
	l->list_size = 1;
	l->arr_size = 0;
	l->list_arr = malloc(sizeof(void*));
	return l;
}

void list_free(list_t l) {
	free(l->list_arr);
	free(l);
}

void list_print(list_t l) {
	/* TODO */
	return 0;
}

int main() {
	list_t list = list_new();
	/*printf("Size: %ld\n", sizeof(void *));
	list[0] = (void*)1;
	printf("%ld\n", (size_t)list[0]);
	list[1] = (void*)6;
	printf("%ld\n", (size_t)list[1]);*/
	list_free(list);
	return 0;
}
