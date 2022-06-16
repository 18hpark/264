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

TreeNode* make_huffman_tree(Node* head) {
	if (head == NULL) {
		return NULL;
	}
	while (head -> next != NULL) {
		TreeNode* tree_node = malloc(sizeof(*tree_node));
		Node* head_left = pq_dequeue(&head);
		Node* head_right = pq_dequeue(&head);
		tree_node -> left = head_left -> a_value;
		tree_node -> right = head_right -> a_value;
		tree_node -> character = '\0';
		tree_node -> frequency = ((TreeNode*)(head_left -> a_value)) -> frequency + ((TreeNode*)(head_right -> a_value)) -> frequency;
		pq_enqueue(&head, tree_node, _compare);
		free(head_left);
		free(head_right);
	}
	TreeNode* node = head -> a_value;
	free(head);
	return node;
}

void destroy_huffman_tree(TreeNode** a_root) {
	if (*a_root != NULL) {
		destroy_huffman_tree(&(*a_root) -> left);
		destroy_huffman_tree(&(*a_root) -> right);
		free(*a_root);
		(*a_root) = NULL;
	}
}

void write_coding_table(TreeNode* root, BitWriter* a_writer) {
	if (root != NULL) {
		write_coding_table(root -> left, a_writer);
		write_coding_table(root -> right, a_writer);
		if ((root -> character) != '\0') {
			write_bits(a_writer, 0x01, 1);	
			write_bits(a_writer, root -> character, 8);
		}
		else {
			write_bits(a_writer, 0x00, 1);
		}
	}
}

typedef struct {
	uint8_t bits;
	int num_bits;
} _BitCode;

static void _assign_bit_code(TreeNode* root, int num_bits, _BitCode* character_to_code, uint8_t bits) {
	if (root != NULL) {
		_assign_bit_code(root -> left, num_bits + 1, character_to_code, bits << 1 | 0);
		_assign_bit_code(root -> right, num_bits + 1, character_to_code, bits << 1 | 1);
		character_to_code[root -> character] = (_BitCode) { .bits = bits, .num_bits = num_bits };
	}
}

void write_compressed(TreeNode* root, BitWriter* a_writer, uint8_t* uncompressed_byte) {
	_BitCode character_to_code[256] = {0};
	_BitCode* modified_code = character_to_code;
	_assign_bit_code(root, 0, modified_code, 0x00);
	int i = 0;
	while (uncompressed_byte[i] != '\0') {
		int selected_char = uncompressed_byte[i];
		write_bits(a_writer, character_to_code[selected_char].bits, character_to_code[selected_char].num_bits);
		i++;
	}
}
