#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sorts.h"

void _print_array(int* array, size_t size, const char* title) {
	printf("%s\n", title);
	for(int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n\n");
}

int main(int argc, char* argv[]) {

	// Demonstrate quick_sort_array(…)
	int array2[] = { 5, 4, 2, 1, 7, 6, 3 };
	size_t size2 = sizeof(array2) / sizeof(*array2);  // # of elements
	_print_array(array2, size2, "Before quick_sort_array(array2)");
	quick_sort_array(array2, size2);
	_print_array(array2, size2, "After  quick_sort_array(array2)");

	return EXIT_SUCCESS;
}
#define DEMO_QSORT_VERSION_1
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
