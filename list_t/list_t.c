#include "list_t.h"

struct list_struct {
	/* How many elements the list holds */
	size_t list_size;
	/* How big the underlying array is */
	size_t arr_size;
	void **list_arr;
};

list_t list_new() {
	list_t l = malloc(sizeof(struct list_struct));
	l->list_size = 0;
	l->arr_size = 1;
	l->list_arr = malloc(sizeof(void*));
	return l;
}

void list_free(list_t l) {
	free(l->list_arr);
	free(l);
}

void list_print(list_t l) {
	size_t i;
	if (l->list_size == 0) {
		printf("[]\n");
		return;
	}
	printf("[");
	for (i = 0; i < l->list_size - 1; i++) {
		printf("%lu, ", (uint64_t)(l->list_arr[i]));
	}
	printf("%lu]\n", (uint64_t)(l->list_arr[l->list_size-1]));
	return;
}

void list_append(list_t l, void *x) {
	size_t i;
	void **tmp;
	/* If no resizing is necessary, just add the element */
	if (l->list_size < l->arr_size) {
		l->list_arr[l->list_size] = x;
		l->list_size += 1;
		return;
	}
	
	/* Not enough space, Resize Array */
	l->arr_size *= 2;
	tmp = malloc(sizeof(void*) * l->arr_size);
	/* Copy elements over into new array */
	for (i = 0; i < l->list_size; i++) {
		tmp[i] = l->list_arr[i];
	}
	free(l->list_arr);
	l->list_arr = tmp;

	/* Actually add the new element */
	l->list_arr[l->list_size] = x;
	l->list_size += 1;
	return;
}

int main() {
	list_t list = list_new();
	size_t i;

	list_print(list);

	for (i = 1; i < 11; i++) {
		list_append(list, (void*)i);
		list_print(list);
	}

	list_free(list);
	return 0;
}
