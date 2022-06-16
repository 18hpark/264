#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"
#include "clog.h"
#include "miniunit.h"
static int _cmp_strings_by_length(const void* a_lhs, const void* a_rhs) {
	size_t len_lhs = strlen(a_lhs);
	size_t len_rhs = strlen(a_rhs);
	return len_lhs - len_rhs;
}

static void _destroy_string(void* string) {
	free(string);
}

/*static int _cmp_string(const void* a_left, const void* a_right) {
	freee(string);
}*/
	
static char* _copy_string(const char* src_string) {
	size_t num_chars = strlen(src_string);
	char* dst_string = malloc(sizeof(*dst_string) * (num_chars + 1));
	return strcpy(dst_string, src_string);
}

int main(int argc, char* argv[]) {
	Node* head = NULL;
	printf("\nTest case: \n");
	pq_enqueue(&head, _copy_string("three"), _cmp_strings_by_length); 
	pq_enqueue(&head, _copy_string("on"), _cmp_strings_by_length);  
	pq_enqueue(&head, _copy_string("o"), _cmp_strings_by_length); 
	pq_enqueue(&head, _copy_string("one"), _cmp_strings_by_length); 
	
	for(Node* curr = head; curr != NULL; curr = curr -> next) {
		printf("%s\n", (char*)(curr -> a_value));
	}

	destroy_list(&head, _destroy_string);
	
	Node* test_head = NULL;
	printf("\ntesting push,pop \n");
	stack_push(&test_head, _copy_string("1"));
	stack_push(&test_head, _copy_string("23"));
	stack_push(&test_head, _copy_string("4"));
	stack_push(&test_head, _copy_string("567"));
	stack_push(&test_head, _copy_string("89"));
	for(Node* curr = test_head; curr != NULL; curr = curr -> next) {
		printf("%s\n", (char*)(curr -> a_value));
	}
	while (test_head != NULL) {
		Node* final = stack_pop(&test_head);
		_destroy_string(final -> a_value);
		free(final);
	}

	return EXIT_SUCCESS;
}
