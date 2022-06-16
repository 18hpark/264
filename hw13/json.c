#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "json.h"

bool parse_int(int* a_value, char const** a_pos) {
	int length = strlen(*a_pos);
	bool is_minus = false;
	(*a_value) = 0;
	for(int i = 0; i < length; i++) {
		if ((*(*a_pos) >= '0' && *(*a_pos) <= '9')) {
			(*a_value) *= 10;
			(*a_value) += (*(*a_pos) - '0');
			(*a_pos)++;
			if (*(*a_pos) == '-' && (*a_value != 0)) {
				return true;
			}
		}
		else if(*(*a_pos) == '+' && (*a_value == 0)) {
			(*a_pos)++;
			if(!(*(*a_pos) >= '0' && *(*a_pos) <= '9')) {
				return false; 
			}
		}
		else if(*(*a_pos) == '-') {
			(*a_pos)++;
			if (*(*a_pos) >= '0' && *(*a_pos) <= '9') {
				is_minus = true;
			}
			else {
				return false; 
			}
		}
		else if (*a_value == 0) {
			return false; 
		}
	}
	if(is_minus == true) {
		(*a_value) = (*a_value) * -1;
	}
	else if(length == 0) {
		return false;
	}
	return true;
}

bool parse_element(Element* a_element, char const** a_pos) {
	bool is_final;
	while (isspace(*(*a_pos)) != false) {
		(*a_pos)++;
	}
	if (isdigit(**a_pos) || (**a_pos) == '-') {
		(*a_element).type = ELEMENT_INT;
		is_final = parse_int(&(a_element -> as_int), a_pos);
	}
	else if (*(*a_pos) == '\"') {
		(*a_element).type = ELEMENT_STRING;
		is_final = parse_string(&(a_element -> as_string), a_pos);
	}
	else if (*(*a_pos) == '[') {
		(*a_element).type = ELEMENT_LIST;
		is_final = parse_list(&(a_element -> as_list), a_pos);
	}
	else {
		return false;
	}
	return is_final;
}

bool parse_string(char** a_string, char const** a_pos) {
	int length = 0;
	if (*(*a_pos) == '\"') {
		(*a_pos)++;
		for (int i = 0; (*a_pos)[i] != '\"'; i++) {
			if((*a_pos)[i] == '\0' || (*a_pos)[i] == '\n') {
				for(int j = 0; j < i; j++) {
					(*a_pos)++;
				}
				return false;
			}
			length++;
		}
	}
	else { 
		return false;
	}
	*a_string = malloc((sizeof(**a_string) * (length + 1)));
	for(int i = 0; *(*a_pos) != '\"'; i++) {
		(*a_string)[i] = *(*a_pos);
		(*a_pos)++;
	}
	(*a_pos)++; //to remove " at the end of string
	(*a_string)[length] = '\0';
	return true;
}

void print_element(Element element) {
	if (element.type == ELEMENT_INT) {
		printf("%d",element.as_int);
	}
	else if (element.type == ELEMENT_STRING) {
		printf("\"%s\"", element.as_string);
	}
	else if (element.type == ELEMENT_LIST) {
		printf("[");
		for (Node* current = element.as_list; current != NULL; current = current -> next) {
			print_element(current -> element);
			if (current -> next != NULL) {
				printf(",");
			}
		}
		printf("]");
	}
}

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) {
		free(element.as_string);
	}
	else if(element.type == ELEMENT_LIST) {
		while (element.as_list != NULL) {
			Node* new_head = (element.as_list) -> next;
			free_element((element.as_list) -> element);
			free(element.as_list);
			element.as_list = new_head;
		}
		element.as_list = NULL;
	}
}

bool parse_list(Node** a_head, char const** a_pos) {
	int length = strlen(*a_pos);
	int closing = length - 2;
	(*a_head) = NULL;
	Node* a_tail = NULL;
	if (*(*a_pos) == '[') {
		(*a_pos)++;
		for (int i = 0; (*a_pos)[i] != ']'; i++) {
			if((*a_pos)[i] == '\0') { //no closing bracket
				return false;
			}
			else if ((*a_pos)[i] == ',') {
				i++;
				if ((*a_pos)[i] == ']' || (*a_pos)[i] == ',' || (*a_pos)[i] == '\0') {
					return false;
				}
			}
		}
		if((*a_pos)[closing] != ']') { //less closing bracket
			return false;
		}
		while (*(*a_pos) != ']') {
			if (*(*a_pos) == ',') {
				(*a_pos)++;
			}
			else if (*(*a_pos) != ',' && (*a_head) != NULL) {
				while ((*a_head) != NULL) {
					Node* new_head = (*a_head) -> next;
					free_element((*a_head) -> element);
					free(*a_head);
					*a_head = new_head;
				}
				return false;
			}
			Node temp_node;
			Node* new_tail;
				if (parse_element(&(temp_node.element), a_pos) == true) {	
					if (*a_head == NULL) {
						*a_head = malloc(sizeof(**a_head)); 
						**a_head = (Node) { .element = temp_node.element, .next = NULL };
						a_tail = *a_head;
					}	
					else {
						new_tail = malloc(sizeof(*new_tail));
						*new_tail = (Node) { .element = temp_node.element, .next = NULL };
						a_tail -> next = new_tail;
						a_tail = new_tail;
					}
				}
			while (isspace(*(*a_pos))) {
				(*a_pos)++;
			}
		}
	}
	if(*(*a_pos) == ']') {
		(*a_pos)++;
		return true;
	}
	return false; //no starting bracket	
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
