#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "sorts.h"

void _insert(int value, BSTNode** root) {
	if (*root == NULL) {
		*root = malloc(sizeof(**root));
		**root = (BSTNode) { .value = value, .left = NULL, .right = NULL };
	}
	else if (value < ((*root) -> value)) {
		_insert(value, &((*root) -> left));
	}
	else {
		_insert(value, &((*root) -> right));
	}
}

void _destroy(BSTNode* root) {
	if (root != NULL) {
		_destroy(root -> left);
		_destroy(root -> right);
		free(root);
	}
	root = NULL;
}

void _fill_array_from_bst(int* array, int* index, BSTNode* root) {
	if (root != NULL) {
		_fill_array_from_bst(array, index, root -> left);
		array[*index] = root -> value;
		(*index)++;
		_fill_array_from_bst(array, index, root -> right);
	}
}

BST create_bst(const int* array, int size) {
	BST bst = (BST) { .root = NULL, .size = 0 };
	for (int i = 0; i < size; i++) {
		_insert(array[i], &(bst.root));
	}
	return bst;
}

void empty_bst(BST* bst) {
	_destroy(bst -> root);
}

void tree_sort_array(int* array, size_t size) {
	int index = 0;
	BST bst = create_bst(array, size);
	_fill_array_from_bst(array, &index, bst.root);
	empty_bst(&bst);
}
