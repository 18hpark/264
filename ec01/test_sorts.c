#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "sorts.h"
void _print_array(int* array, size_t size, const char* title) {
	printf("%s\n", title);
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

int main(int argc, char* argv[]) {
	int array1[] = {5, 4, 2, 1, 7, 6, 3};
	size_t size1 = sizeof(array1) / sizeof(*array1);
	_print_array(array1, size1, "Before quick_sort_array(array1)");
	quick_sort_array(array1, size1);
	_print_array(array1, size1, "After quick_sort_array(array1)");

	return EXIT_SUCCESS;
}
