#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "priority_queue.h"
Node* pq_enqueue(Node** a_head, void* a_value, int (*cmp_fn)(const void*, const void*)) {
	Node* new_node = malloc(sizeof(*new_node));
	*new_node = (Node) { .a_value = a_value, .next = *a_head};

	if ((*a_head) == NULL || a_value == NULL || cmp_fn((*a_head) -> a_value, new_node -> a_value) >= 0 ) {
		*a_head = new_node;
	}
	else {
		new_node -> next = (*a_head) -> next;
		Node* temp = (*a_head);
		while ((temp -> next != NULL) && (cmp_fn(new_node -> a_value, temp -> next -> a_value) >= 0)) {
			temp = temp -> next;
		}
		new_node -> next = temp -> next;
		temp -> next = new_node;
	}
	return new_node; 
}

Node* pq_dequeue(Node** a_head) {
	Node* removed_node = *a_head;
	if (*a_head != NULL) {
		*a_head = (*a_head) -> next;
		removed_node -> next = NULL;
	}
	return removed_node;  
}

Node* stack_push(Node** a_head, void* a_value) {
	return pq_enqueue(a_head, a_value, NULL); 
}

Node* stack_pop(Node** a_head) {
	return pq_dequeue(a_head); 
}

void destroy_list(Node** a_head, void (*destroy_value_fn)(void*)) {
	for(int i = 0; *a_head != NULL; i++){
		Node* removed_node = pq_dequeue(a_head);
		destroy_value_fn(removed_node -> a_value);
		free(removed_node);
	}
}
#define HUFFMAN_C_V1
