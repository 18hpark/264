#include <stdlib.h>

typedef struct _BSTNode {
	int value;
	struct _BSTNode* left;
	struct _BSTNode* right;
} BSTNode;

typedef struct {
	BSTNode* root;
	int size;
} BST;

BST create_bst(const int* array, int size);
void empty_bst(BST* bst);
void tree_sort_array(int* array, size_t size);

