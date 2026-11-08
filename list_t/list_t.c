#include "list_t.h"

/*struct list {
	size_t list_size;
	size_t arr_size;
	void **list_arr;
};

list_t list_new() {
	list_t l = malloc(sizeof(size_t));
	l->list_size = 0;
	l->arr_size = 0;
	l->list_arr = 1;
	return l;
}*/

struct list {
	int x;
	void **list_arr;
};

list_t list_new() {
	list_t l = malloc(sizeof(int) + (sizeof(void*) * 2));
	l->x = 1;
	l->list_arr[0] = 0;
	return l;
}

int main() {
	list_t list = list_new();
	/*printf("Size: %ld\n", sizeof(void *));
	list[0] = (void*)1;
	printf("%ld\n", (size_t)list[0]);
	list[1] = (void*)6;
	printf("%ld\n", (size_t)list[1]);*/
	free(list);
	return 0;
}
