#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "miniunit.h"
#include <limits.h>

static int _test_list_empty() {
	mu_start();
	Element element;
	char const* pos = "[]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list == NULL);
		free_element(element);
	}
	mu_end();
}

static int _test_list_int() {
	mu_start();
	Element element;
	char const* pos = "[1]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list != NULL);
		mu_check(element.as_list -> element.as_int == 1);
		mu_check(element.as_list -> element.type == ELEMENT_INT);
		free_element(element);
	}
	mu_end();
}

static int _test_list_of_list() {
	mu_start();
	Element element;
	char const* pos = "[\"A\",\"B\",[123,345]]";
	bool is_success = parse_element(&element, &pos); //here
	mu_check(is_success);
	free_element(element);
	mu_end();
}

static int _test_list_two_ints() {
	mu_start();
	Element element;
	char const* pos = "[12,34]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list != NULL);
		mu_check(element.as_list -> element.as_int == 12);
		mu_check(element.as_list -> element.type == ELEMENT_INT);
		mu_check(element.as_list -> next != NULL);
		mu_check(element.as_list -> next -> element.as_int == 34);
		mu_check(element.as_list -> next -> element.type == ELEMENT_INT);
		free_element(element);
	}
	mu_end();
}

static int _test_list_two_ints_with_space() {
	mu_start();
	Element element;
	char const* pos = "[12    ,34]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list != NULL);
		mu_check(element.as_list -> element.as_int == 12);
		mu_check(element.as_list -> element.type == ELEMENT_INT);
		mu_check(element.as_list -> next != NULL);
		mu_check(element.as_list -> next -> element.as_int == 34);
		mu_check(element.as_list -> next -> element.type == ELEMENT_INT);
		free_element(element);
	}
	mu_end();
}


static int _test_list_two_chars() {
	mu_start();
	Element element;
	char const* pos = "[\"QhjdaskW\"]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list != NULL);
		mu_check(element.as_list -> element.type == ELEMENT_STRING);
		mu_check_strings_equal("QhjdaskW",(element.as_list -> element.as_string));
		free_element(element);
	}
	mu_end();
}


static int _test_list_of_edge_case() {
	mu_start();
	Element element;
	char const* pos = "[[[[[[[[1234]]]]]]]]";
	bool is_success = parse_element(&element, &pos); //here
	mu_check(is_success);
	free_element(element);
	mu_end();
}

static int _test_print_list_ofint() {
	mu_start();
	Element element;
	char const* input = "[123,456,789]";
	parse_element(&element, &input);
	printf("Test parse_element(&element, [123,456,789])\n");
	printf("Expected : [123,456,789]\n");
	printf("Actual : ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
	mu_end();
}

static int _test_list_three_ints() {
	mu_start();
	Element element;
	char const* pos = "[12,34,56]";
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	if (is_success) {
		mu_check(element.type == ELEMENT_LIST);
		mu_check(element.as_list != NULL);
		mu_check(element.as_list -> element.as_int == 12);
		mu_check(element.as_list -> element.type == ELEMENT_INT);
		mu_check(element.as_list -> next != NULL);
		mu_check(element.as_list -> next -> element.as_int == 34);
		mu_check(element.as_list -> next -> element.type == ELEMENT_INT);
		mu_check(element.as_list -> next -> next != NULL);
		mu_check(element.as_list -> next -> next -> element.as_int == 56);
		mu_check(element.as_list -> next -> next -> element.type == ELEMENT_INT);
		free_element(element);
	}
	mu_end();
}

static int _test_list_invalid(){
	mu_start();
	Element element;
	char const* pos = "[";
	bool is_success = parse_element(&element, &pos);	
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[[";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "]"; 
	is_success = parse_element(&element, &pos);		
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	/*pos = "[\"123\"]]";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);//error */
	//-------------------------------------------------------------------------------
	pos = "[[[[]";	
	is_success = parse_list(&(element.as_list), &pos);
	mu_check(!is_success);/*
	//-------------------------------------------------------------------------------
	pos = "][]";	
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[1 2, 3]";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[]]]]";
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	//-------------------------------------------------------------------------------
	pos = "[,";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "123";
	is_success = parse_list(&(element.as_list), &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[,";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[][][[[";
	is_success = parse_element(&element, &pos);
	mu_check(is_success);
	//-------------------------------------------------------------------------------
	mu_end();
	pos = "[1,,,3]";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);
	//-------------------------------------------------------------------------------
	pos = "[12,,12,,12]";
	is_success = parse_element(&element, &pos);
	mu_check(!is_success);*/
	//-------------------------------------------------------------------------------
	mu_end();
}

static int _test_parse_element_string() {
	mu_start();
	Element element;
	char const* input = "\"ABC\"";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABC", element.as_string);
	mu_check(element.type == ELEMENT_STRING);
	mu_check(pos == input + 5);
	mu_check(*pos == '\0');
	free_element(element);
	mu_end();
}

static int _test_print_element_invalid() {
	mu_start();
	Element element;
	char const* input = "ABC";
	char const* pos = input;
	bool is_success = parse_element(&element, &input);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_end();
}

static void _test_print_element() {
	Element element;
	char const* input = "123";
	parse_element(&element, &input); 
	printf("Testing parse_element(&element, \"123\")\n");
	printf(" - Expected: 123\n");
	printf(" - Actual: ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
}

static int _test_print_element_two() {
	mu_start();
	Element element;
	char const* input = "\"ABC\"";
	parse_element(&element, &input);
	printf("Testing parse_element(&element, \"\\\"ABC\\\"\")\n");
	printf(" - Expected: \"ABC\"\n");
	printf(" - Actual: ");
	print_element(element);
	fputc('\n', stdout);
	free_element(element);
	mu_end();
}

static int _test_parse_string_valid_empty() {
	mu_start();
	char* result;
	char const* input = "\"\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("", result);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	free(result);
	mu_end();
}

static int _test_parse_string_valid_one_char() {
	mu_start();
	char* result;
	char const* input = "\"A\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("A", result);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	free(result);
	mu_end();
}

static int _test_parse_string_valid_multiple_chars() {
	mu_start();
	char* result;
	char const* input = "\"ABCDFG\"";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(is_success);
	mu_check_strings_equal("ABCDFG", result);
	mu_check(pos == input + 8);
	mu_check(*pos == '\0');
	free(result);
	mu_end();
}

static int _test_parse_string_invalid() {
	mu_start();
	char* result;
	char const* input = "\"A";
	char const* pos = input;
	bool is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	
	input = "\"A\nB\"";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');

	input = "\"A\nB";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 2);
	mu_check(*pos == '\n');

	input = "AB";
	pos = input;
	is_success = parse_string(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_check(*pos == 'A');
	mu_end();
}

static int _test_parse_element_int_plain() {
	mu_start();
	Element element;
	char const* input = "1ABC";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 1);
	mu_check(*pos == 'A');
	mu_end();
}

static int _test_parse_element_int_negative_numbers() {
	mu_start();
	Element element;
	char const* input = "-2";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == -2);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == '\0');
	mu_end();
}

static int _test_parse_element_with_leading_whitespace() {
	mu_start();
	Element element;
	char const* input = "  1";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 1);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 3);
	mu_check(*pos == '\0');
	mu_end();
}

static int _test_parse_element_int_oddballs() {
	mu_start();
	Element element;
	char const* input = " 4 A";
	char const* pos = input;
	bool is_success = parse_element(&element, &pos);
	mu_check(is_success);
	mu_check(element.as_int == 4);
	mu_check(element.type == ELEMENT_INT);
	mu_check(pos == input + 2);
	mu_check(*pos == ' ');
	mu_end();
}

int _test_parse_int_valid() {
	mu_start();
	int result;
	char* input = "123";	
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 3);
	mu_check(result == 123);	
	mu_end();
}

int _test_parse_int_positive() {
	mu_start();
	int result;
	char* input = "+A";		
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_end();
}

int _test_parse_int_negative() {
	mu_start();
	int result;
	char* input = "-123";	
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(result == -123);	
	mu_end();
}

int _test_parse_int_negative_sign() {
	mu_start();
	int result;
	char* input = "-";		
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input + 1);
	mu_end();
}

int _test_parse_int_empty() {
	mu_start();
	int result;
	char* input = "";			
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_end();
}


int _test_parse_int_zero() {
	mu_start();
	int result;
	char* input = "00";		
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 2);
	mu_check(result == 0);		
	mu_end();
}

int _test_parse_int_negative_zero() {
	mu_start();
	int result;
	char* input = "-005";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 4);
	mu_check(result == -5);
	mu_end();
}

int _test_parse_int_invalid() {
	mu_start();
	int result;
	char* input = "A";
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(!is_success);
	mu_check(pos == input);
	mu_end();
}

int _test_parse_int_middle_sign() {
	mu_start();
	int result;
	char* input = "1-1";		
	char const* pos = input;
	bool is_success = parse_int(&result, &pos);
	mu_check(is_success);
	mu_check(pos == input + 1);
	mu_check(result == 1);		
	mu_end();
}


int main(int argc, char* argv[]) {
	mu_run(_test_list_empty);
	mu_run(_test_list_int);
	mu_run(_test_list_two_chars);
	mu_run(_test_list_two_ints);
	mu_run(_test_list_three_ints);
	
	mu_run(_test_list_invalid);
	mu_run(_test_list_of_list);
	mu_run(_test_list_of_edge_case);

	mu_run(_test_print_list_ofint);

	mu_run(_test_list_two_ints_with_space);

	mu_run(_test_print_element_invalid);
	mu_run(_test_print_element_two);
	mu_run(_test_parse_element_string);

	_test_print_element();

	mu_run(_test_parse_string_valid_empty);
	mu_run(_test_parse_string_valid_one_char);
	mu_run(_test_parse_string_valid_multiple_chars);
	mu_run(_test_parse_string_invalid);

	mu_run(_test_parse_element_int_plain);
	mu_run(_test_parse_element_int_negative_numbers);
	mu_run(_test_parse_element_with_leading_whitespace);
	mu_run(_test_parse_element_int_oddballs);

	mu_run(_test_parse_int_valid);
	mu_run(_test_parse_int_positive);
	mu_run(_test_parse_int_negative);
	mu_run(_test_parse_int_negative_sign);
	mu_run(_test_parse_int_empty);
	mu_run(_test_parse_int_zero);
	mu_run(_test_parse_int_negative_zero);
	mu_run(_test_parse_int_invalid);
	mu_run(_test_parse_int_middle_sign);
	return EXIT_SUCCESS;
}

