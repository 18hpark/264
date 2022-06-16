#include <stdio.h>
#include "print_integer.h"

//A helper function to reduce the redundancy of the primary function print_integer
void display_result(int remainder) 		
{
	if (remainder > 9)
	{
		remainder -= 10;
		fputc('a' + remainder, stdout);
	}
	else
	{
		fputc('0' + remainder, stdout);
	}
}

void print_integer(int n, int radix, char* prefix)
{
	//if n is a negative number, print - and change it to absolute number
	unsigned int n_abs;
	if (n < 0)
	{
		fputc('-', stdout);
		n_abs = -n;
	}
	else 
	{
		n_abs = n;
	}
	//print prefix
	for (int i = 0; prefix[i] != '\0'; i++)
	{
		fputc(prefix[i], stdout);
	}
	//print number to changed radix
	int remain;
	if (n_abs >= radix)
	{
		print_integer(n_abs / radix, radix, "");		//Performing recursion
		remain = n_abs % radix;
		display_result(remain);							//Calling helper function
	}
	else
	{
		display_result(n_abs);							//Calling helper function
	}
}
