#include <stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[]) {
	// Test 00: empty test
	// Expect: ""

	// Test 01: empty string
	mintf("");
	// Expect: ""
	
	// Test 02: print string
	mintf("19990403");
	// Expect: "19990403"
	
	// Test 03: print string using %s
	mintf("%s 19990403", "Print");
	// Expect: "Print 19990403"
		
	// Test 04: print number and string using %d and %s
	mintf("Favorite number is %d and my major is %s", 7, "ComputerEngineering");
	// Expect: "Favorite number is 7 and my major is CompuerEngineering"

	// Test 05: add aditional number using %d to verify if redundancy could cause an error
	mintf("Number %d is %s than %d", 7, "bigger", 5);
	// Expect: "Number 7 is bigger than 5"

	// Test 06: print binary, number, and string using %b, %d, and %s
	mintf("%s's birth date is %d and it could be written in binary as %b", "Jared", 19990403, 19990403);
	// Expect: "Jared's birth date is 19990403 and it could be written in binary as 1001100010000011110000011"
		
	// Test 07: add another binary to previous test to verify if multiple binary could cause error due to redundancy
	mintf("%d in %s is %b and 12 in binary is %b ", 8, "binary", 8, 12);
	// Expect: "8 in binary is 1000 and 12 in binary is 1100"

	// Test 08: print binary, hexadecimal, number, and string using %b, %x, %d, and %s
	mintf("%s %d could be written as %b in binary or %x in hexadecimal", "Number", 20, 20, 20);
	// Expect: "Number 20 could be written as 10100 in binary or 14 in hexadecimal"

	// Test 09: print binary, hexadecimal, dollar sign, number and multiple strings using %b, %x, %$, %d, and %s	
	mintf("%s %$ by %x/%b/%d (MM/DD/YEAR)", "I wish my bank balance was", 999999, 4, 1, 2025);
	// Expect: "I wish my bank balance was $9999.99 by 4/1/2025 (MM/DD/YEAR)"

	// Test 10: add percent sign to previous test using %%
	mintf("%s 50%% is %$ and this sale is until %x/%b/%d (MM/DD/YEAR)", "The price after being discounted by", 9999, 4, 1, 2022);
	// Expect: "The price after being discounted by 50% is $99.99 and this sale is until 4/1/2022 (MM/DD/YEAR)"
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
