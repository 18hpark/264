#include <stdio.h>
#include "mintf.h"
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

//A helper function to reduce the redundancy of the primary function print_integer
void _display_result(int remainder) {
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

void print_integer(int n, int radix, char* prefix) {
	//if n is a negative number, print - and change it to absolute number
	unsigned int n_abs;
	if (n < 0) {
		fputc('-', stdout);
		n_abs = -n;
	}
	else {
		n_abs = n;
	}
	//print prefix
	for (int i = 0; prefix[i] != '\0'; i++) {
		fputc(prefix[i], stdout);
	}
	//print number to changed radix
	int remain;
	if (n_abs >= radix) {
		print_integer(n_abs / radix, radix, "");		//Performing recursion
		remain = n_abs % radix;
		_display_result(remain);							//Calling helper function
	}
	else {
		_display_result(n_abs);							//Calling helper function
	}
}

void mintf(const char *format, ...) {
	va_list more_args;
	va_start(more_args, format);

	for(int i = 0; format[i] != '\0'; i++) {
		if(format[i] == '%') {
			i++;
			if(format[i] == 'd') {
				int number = va_arg(more_args, int);
				print_integer(number, 10, "");
			}
			else if(format[i] == 'b') {
				int number = va_arg(more_args, int);
				print_integer(number, 2, "0b");
			}
			else if(format[i] == 'x') {
				int number = va_arg(more_args, int);
				print_integer(number, 16, "0x");
			}
			else if(format[i] == 's') {
				char* phrase = va_arg(more_args, char*);
				for(int j = 0; phrase[j] != '\0'; j++) {
					fputc(phrase[j], stdout);
				}
			}
			else if(format[i] == 'c') {
				char alphabet = va_arg(more_args, int);
				fputc(alphabet, stdout);
			}
			else if(format[i] == '%') {
				fputc('%', stdout);
			}
			else if(format[i] == '$') {
				int number = va_arg(more_args, int);
				unsigned int absolute_value = number;
				if(number < 0) {
					fputc('-', stdout);
					absolute_value = number * -1;
				}
				int quotient = absolute_value / 100;
				print_integer(quotient, 10, "$");
				int remainder = absolute_value % 100;
				if(remainder < 10) {
					print_integer(remainder, 10, ".0");
				}
				else {
					print_integer(remainder, 10, ".");
				}
			}
			else {
				i--;
				fputc(format[i], stdout);
			}
		}
		else {
			fputc(format[i], stdout);
		}
	}
	va_end(more_args);
}
