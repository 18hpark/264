#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "smintf.h"
#include "miniunit.h"


int _test_empty() {
	mu_start();
	mu_check_smintf("", "");
	mu_end();
}

int _test_simple() {
	mu_start();
	mu_check_smintf("3", "%d", 3);
	//mu_check_smintf("0b11110", "%b", 30);
	//mu_check_smintf("-0x28", "%x", -40);
	//mu_check_smintf("C", "%c", 'C');
	//mu_check_smintf("100%", "100%%");
	//mu_check_smintf("$199.99", "%$", 19999);
	//mu_check_smintf("-$1.01", "%$", -101);
	//mu_check_smintf("0x2f", "%x", 47);
	//mu_check_smintf("Hello my name is Jared", "Hello my name is %s", "Jared");
	mu_end();
}

int _test_complex() {
	mu_start();
	mu_check_smintf("%$99.99", "%%%$", 9999);
	mu_check_smintf("%g", "%g");
	mu_check_smintf("ECE 0x108 Jared has A", "%s %x Jared has %c", "ECE", 264, 'A');
	//mu_check_smintf("0b11110 c $99.99", "%b %c %$", 30, 'c', 9999);
	mu_check_smintf("-2147483648", "%d", INT_MIN);
	mu_check_smintf("2147483647", "%d", INT_MAX);
	mu_end();
}

int main(int argc, char* argv[]) {
	//mu_run(_test_empty);
	mu_run(_test_simple);
	mu_run(_test_complex);

	return EXIT_SUCCESS;
}
