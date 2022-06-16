#include <stdio.h>
#include <stdlib.h>
#include "count_words.h"
#include "miniunit.h"

int _test_empty() {
	mu_start();
	mu_check(count_words("") == 0);
	mu_end();
}

int _test_simple() {
	mu_start();
	mu_check(count_words("apple") == 1);
	mu_check(count_words("boring boxes") == 2);
	mu_check(count_words("apple banana") == 3);
	mu_check(count_words("apple cherry kiwi") == 4);
	mu_end();
}

int _test_hard() {
	mu_start();
	mu_check(count_words("famigerate fiddle-faddle") == 2);
	mu_check(count_words("Mary's mongoose") == 3);
	mu_check(count_words("plumbers' platitudes") == 2);
	mu_end();
}

int _test_compare() {
	mu_start();
	mu_check_strings_equal("Apple Dinosaurs latino", "Apple Dinosaurs latino");
	mu_check_strings_equal("Apple Dinosaurs latino", "Help Kid");
	mu_end();
}

int main(int argc, char* argv[]) {

	mu_run(_test_empty);
	mu_run(_test_simple);
	mu_run(_test_hard);
	mu_run(_test_compare);

	log_int(count_words("My apples are sweet."));
	log_int(count_words("My friends' apples are sweeter.")); // "'" after s
	log_int(count_words("My friend's apples are sweeter.")); // "'" before s
	log_int(count_words("A pear is sweeter than an apple.."));

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
