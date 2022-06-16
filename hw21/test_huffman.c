#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "huffman.h"
#include "miniunit.h"

static char const* _write_file(char const* contents, char const* filename) {
	FILE* fp = fopen(filename, "w");
	fputs(contents, fp);
	fclose(fp);
	return filename;
}

static int _test_one() {
	mu_start();
	char const* path = _write_file("abc\nabca\n", "official.txt");
	Frequencies freqs = {0};
	char const* error = NULL;
	bool is_success_calc = calc_frequencies(freqs, path, &error);
	Node* head = make_huffman_pq(freqs);
	//mu_check(((Treenode*)(head -> a_value != NULL);
	mu_check(is_success_calc);
	TreeNode* tree_node = make_huffman_tree(head);

	destroy_huffman_tree(&tree_node);
	mu_end();
}


static int _test_valid_two() {
	mu_start();
	char const* path = _write_file("huffman fluffs many mums", "valid_text.txt");
	Frequencies freqs = {0};
	char const* error = NULL;
	bool is_success_calc = calc_frequencies(freqs, path, &error);
	Node* head = make_huffman_pq(freqs);
	TreeNode* root = make_huffman_tree(head);
	BitWriter writer = open_bit_writer("huffman.txt");
	write_coding_table(root, &writer);
	mu_check(is_success_calc);
	mu_check(&writer != NULL);
	close_bit_writer(&writer);
	destroy_huffman_tree(&root);
	mu_end();
}

static int _test_valid_three() {
	mu_start();
	char const* path = _write_file("huffman fluffs many mums", "valid_text.txt");
	Frequencies freqs = {0};
	char const* error = NULL;
	unsigned char encode_txt[] = "huffman fluffs many mums";
	uint8_t* converted_txt = encode_txt;
	if (calc_frequencies(freqs, path, &error)) {
		Node* head = make_huffman_pq(freqs);
		TreeNode* root = make_huffman_tree(head);
		BitWriter writer = open_bit_writer("test3.txt");
		write_compressed(root, &writer, converted_txt);	
		close_bit_writer(&writer);
		destroy_huffman_tree(&root);
	}
	mu_end();
}

static int _test_invalid() {
	mu_start();
	char const* path = "invalid.txt";
	Frequencies freqs = {0};
	char const* error = NULL;
	bool is_success_calc = calc_frequencies(freqs, path, &error);
	Node* head = make_huffman_pq(freqs);
	mu_check(!is_success_calc);
	TreeNode* tree_node = make_huffman_tree(head);
	mu_check(tree_node == NULL);
	mu_end();
}

int main(int argc, char* argv[]) {
	mu_run(_test_one);
	mu_run(_test_valid_two);
	mu_run(_test_valid_three);
	mu_run(_test_invalid);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
