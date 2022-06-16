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

static void _destroy_helper(void* value) {
	TreeNode* temp = (TreeNode*)value;
	if (temp != NULL) {
		_destroy_helper(temp -> left);
		_destroy_helper(temp -> right);
		free(temp);
	}
}

static int _test_one() {
	mu_start();
	char const* path = _write_file("abc\nabca\n", "official.txt");
	Frequencies freqs = {0};
	char const* error = NULL;
	bool is_success = calc_frequencies(freqs, path, &error);
	Node* head = make_huffman_pq(freqs);
	//mu_check(((Treenode*)(head -> a_value != NULL);
	mu_check(is_success);
	destroy_list(&head, _destroy_helper);
	mu_end();
}


int main(int argc, char* argv[]) {
	mu_run(_test_one);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
