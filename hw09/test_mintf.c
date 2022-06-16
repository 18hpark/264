#include <stdlib.h>
#include "mintf.h"
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

int main(int argc, char* argv[]) {
	//Test 1: One decimal number with %d
	mintf("129384: %d", 129384);
	fputc('\n', stdout);
	//Test 2: One negative decimal number with %d
	mintf("-992838: %d", -992838);
	fputc('\n', stdout);
	//Test 3: Multiple decimal number with %d	
	mintf("%d %d %d %d %d", -123, 100, 0, 1, 4789);
	fputc('\n', stdout);
	//Test 4: INT_MIN and INT_MAX with %d
	mintf("Min: %d and Max: %d", INT_MIN, INT_MAX);
	fputc('\n', stdout);

	//Test 5: One binary number with %b
	mintf("1101: %b", 13);
	fputc('\n', stdout);
	//Test 6: One negative binary number with %b
	mintf("-1101: %d", -13);
	fputc('\n', stdout);
	//Test 7: Multiple binary number with %b	
	mintf("%b %b %b", -13, 0, 13);
	fputc('\n', stdout);
	//Test 8: INT_MIN and INT_MAX with %b
	mintf("Min: %b and Max: %b", INT_MIN, INT_MAX);
	fputc('\n', stdout);

	//Test 9: One hexadecimal number with %x
	mintf("%x", 113);
	fputc('\n', stdout);
	//Test 10: One negative hexadecimal number with %x
	mintf("%x", -1323);
	fputc('\n', stdout);
	//Test 11: Multiple hexadecimal number with %x
	mintf("%b %b %b", -15, 0, 47);
	fputc('\n', stdout);
	//Test 12: INT_MIN and INT_MAX with %x
	mintf("Min: %x and Max: %x", INT_MIN, INT_MAX);
	fputc('\n', stdout);

	//Test 13: one %$
	mintf("%$", 1323);
	fputc('\n', stdout);
	//Test 14: One negative %$
	mintf("%$", -1323);
	fputc('\n', stdout);
	//Test 15: Multiple %$	
	mintf("%$ %$ %$", -2, 0, 15);
	fputc('\n', stdout);
	//Test 16: INT_MIN and INT_MAX with %$
	mintf("Min: %$ and Max: %$", INT_MIN, INT_MAX);
	fputc('\n', stdout);

	//Test 17: one character
	mintf("%c", 113);
	fputc('\n', stdout);
	//Test 18: Multiple characters
	mintf("%c %c %c",'A', 57, 102);
	fputc('\n', stdout);

	//Test 19: one string with %s
	mintf("%s", "Stirng");
	fputc('\n', stdout);
	//Test 20: multiple strings with %s
	mintf("%s %s", "multiple", "strings");
	fputc('\n', stdout);

	//Test 21: one %% with % in a sentence
	mintf("11% 11%%");
	fputc('\n', stdout);
	//Test 22: three %%
	mintf("Two % needed. %%%");
	fputc('\n', stdout);

	//Test 23: Excess parameters
	mintf("%d %d", 1, 2, 3, 4);
	fputc('\n', stdout);
	//Test 24: Insufficient parameters
	mintf("%s %d %c", "string", 1233);
	fputc('\n', stdout);
	//Test 25: Mismatched parameters
	//mintf("%c %s %d", 277, 12, "last");
	//gives me segmentation fault

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
