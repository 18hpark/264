#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "sorts.h"

int _compare_fn_for_qsort(const void* o1, const void* o2) {
	return (*(int*)o1) - (*(int*)o2);
}

void quick_sort_array(int* array, size_t size) {
	qsort(array, size, sizeof(int), _compare_fn_for_qsort);
}
