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
		printf("[]");
		return;
	}
	printf("[");
	for (i = 0; i < l->list_size - 1; i++) {
		printf("%lu, ", (uint64_t)(l->list_arr[i]));
	}
	printf("%lu]", (uint64_t)(l->list_arr[l->list_size-1]));
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

void list_extend(list_t l1, list_t l2) {
	size_t i, new_s;
	void** tmp;
	/* If we don't need to resize l1, just copy elements over */
	if (l1->list_size + l2->list_size <= l1->arr_size) {
		for (i = 0; i < l2->list_size; i++) {
			l1->list_arr[l1->list_size + i] = l2->list_arr[i];
		}
		l1->list_size += l2->list_size;
		return;
	}

	/* If we do need to resize l1 */

	/* Start with the bigger array size */
	if (l1->arr_size > l2->arr_size) {
		new_s = l1->arr_size;
	}
	else {
		new_s = l2->arr_size;
	}
	
	/* Count up to obtain the new arr_size which can fit all elements,
	 * while maintaining the property that arr_size is a multiple of 2 */
	while (new_s < l1->list_size + l2->list_size) {
		new_s *= 2;
	}

	/* Make the new array and copy over all values into it,
	 * appending l2 to the l1 values in the process */
	tmp = malloc(sizeof(void*) * new_s);
	for (i = 0; i < l1->list_size; i++) {
		tmp[i] = l1->list_arr[i];
	}
	for (i = 0; i < l2->list_size; i++) {
		tmp[l1->list_size + i] = l2->list_arr[i];
	}
	
	/* Remember to update the list_size and arr_size */
	l1->list_size += l2->list_size;
	l1->arr_size = new_s;

	/* Swap the old array for the new one */
	free(l1->list_arr);
	l1->list_arr = tmp;

	return;
}

void list_insert(list_t l, size_t i, void *x) {
	size_t j;
	void **tmp;
	/* If no resizing is necessary */
	if (l->list_size < l->arr_size) {
		/* Move all items to the right of the desired location (and the location itself)
		 * over by one to make room */
		for (j = l->list_size; j > i; j--) {
			l->list_arr[j] = l->list_arr[j-1];
		}
		/* Add the new item (and update size) */
		l->list_arr[i] = x;
		l->list_size += 1;
		return;
	}
	
	/* Not enough space, Resize Array */
	l->arr_size *= 2;
	tmp = malloc(sizeof(void*) * l->arr_size);
	/* Copy elements over the new array
	 * For a slight optimization, add the new element while copying over,
	 * so it is not necessary to shift the array elements again */
	for (j = 0; j < i; j++) {
		tmp[j] = l->list_arr[j];
	}
	tmp[i] = x;
	for (j = i; j < l->list_size; j++) {
		tmp[j+1] = l->list_arr[j];
	}

	l->list_size += 1;

	free(l->list_arr);
	l->list_arr = tmp;

	return;
}

bool list_remove(list_t l, void *x) {
	size_t i, j;

	for (i = 0; i < l->list_size; i++) {
		if (l->list_arr[i] == x) {
			for (j = i; j < l->list_size-1; j++) {
				l->list_arr[j] = l->list_arr[j+1];
			}
			l->list_size -= 1;
			return TRUE;
		}
	}

	return FALSE;
}

void* list_pop(list_t l, size_t i) {
	size_t j, k;
	void* tmp;
	if (i > l->list_size) {
		fprintf(stderr, "Error: List index out of bounds. Exiting...");
		exit(1);
	}
	tmp = l->list_arr[i];
	for (j = i; j < l->list_size-1; j++) {
		l->list_arr[j] = l->list_arr[j+1];
	}
	l->list_size -= 1;
	return tmp;
}

int main() {
	list_t l = list_new();
	list_t l2 = list_new();
	size_t i, tmp;


	for (i = 1; i < 6; i++) {
		list_append(l, (void*)i);
	}

	printf("Initial list: ");
	list_print(l);
	printf("\n\n");

	for (i = 1; i < 6; i++) {
		list_append(l2, (void*)(i * 100));
	}

	printf("Second list: ");
	list_print(l2);
	printf("\n\n");

	list_extend(l, l2);

	printf("After extension:\nl: ");
	list_print(l);
	printf("\nl2: ");
	list_print(l2);
	printf("\n\n");

	l2->list_arr[0] = (void*)200;

	printf("After l2 change:\nl: ");
	list_print(l);
	printf("\nl2: ");
	list_print(l2);
	printf("\n\n");

	list_insert(l, 2, (void*)52);

	printf("After insertion at index 2:\nl: ");
	list_print(l);
	printf("\n\n");

	for (i = 3; i < 9; i++) {
		list_insert(l, 2, (void*)(50 + i));
	}

	printf("After six more insertions as index 2:\nl: ");
	list_print(l);
	printf("\n\n");

	list_remove(l, (void*)52);
	
	printf("After removing 52:\nl: ");
	list_print(l);
	printf("\n\n");

	tmp = (size_t)list_pop(l, 2);

	printf("After popping %lu from index 2:\nl: ", tmp);
	list_print(l);
	printf("\n\n");

	list_free(l);
	list_free(l2);
	return 0;
}
