#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "print_integer.h"

int main(int argc, char* argv[]) {
	print_integer(INT_MIN, 10, "");
	fputc('\n', stdout);
	
	print_integer(INT_MAX, 10, "");
	fputc('\n', stdout);

	print_integer(232883, 15, "#$");
	fputc('\n', stdout);
	
	print_integer(-17117, 14, "");
	fputc('\n', stdout);

	print_integer(29309, 7, "0sd");
	fputc('\n', stdout);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
