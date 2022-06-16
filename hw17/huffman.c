#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "huffman.h"

static int _compare(const void* node_left, const void* node_right) {
	TreeNode* tree_left = (TreeNode*)node_left;
	TreeNode* tree_right = (TreeNode*)node_right;
	if (tree_left -> frequency == tree_right -> frequency) {
		return (int*)(tree_left) - (int*)(tree_right);
	}
	else {
		return (int)(tree_left -> frequency) - (int)(tree_right -> frequency);
	}
}
	
Node* make_huffman_pq(Frequencies freqs) {
	Node* head = NULL;
	for (int i = 0; i < 256; i++) {
		if (freqs[i] != 0) {
			TreeNode* new_node = malloc(sizeof(*new_node));
			*new_node = (TreeNode) { .left = NULL, .right = NULL, .character = (char)i, .frequency = freqs[i] };
			pq_enqueue(&(head), new_node, _compare);
		}
	}
	return head;
}
