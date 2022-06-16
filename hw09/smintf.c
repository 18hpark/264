#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include "smintf.h"
#include <stdio.h>


static void _save_result(int remainder, char** buffer) {
	if (remainder > 9) {
		remainder -= 10;
		*(*buffer) = 'a' + remainder;
		(*buffer)++;
	}
	else {
		*(*buffer) = '0' + remainder;
		(*buffer)++;
	}
}


static void _find_length(int n, int radix, char* prefix, int* length) {
	unsigned int n_abs;
	if (n < 0) {
		(*length)++;
		n_abs = -n;
	}
	else {
		n_abs = n;
	}

	for (int i = 0; prefix[i] != '\0'; i++) {
		(*length)++;
	}

	if (n_abs >= radix) {
		_find_length(n_abs / radix, radix, "", length);		
		(*length)++;
	}
	else {
		(*length)++;
	}
}

static void _to_string(int n, int radix, char* prefix, char** buffer) {
	unsigned int n_abs;

	if (n < 0) {
		*(*buffer) = '-';
		(*buffer)++;
		n_abs = -n;
	}
	else {
		n_abs = n;
	}

	for (int i = 0; prefix[i] != '\0'; i++) {
		*(*buffer) = prefix[i];
		(*buffer)++;
	}
	
	int remain;
	if (n_abs >= radix) {
		_to_string(n_abs / radix, radix, "", buffer);		
		remain = n_abs % radix;
		_save_result(remain, buffer);
	}
	else {
		_save_result(n_abs, buffer);	
	}
}

char* smintf(const char *format, ...) {
	va_list more_args;
	va_start(more_args, format);
	
	int length = 0;

	for(int i = 0; format[i] != '\0'; i++) {
		if(format[i] == '%') {
			i++;
			if(format[i] == 'd') {
				int number = va_arg(more_args, int);
				_find_length(number, 10, "", &length);
			}
			else if(format[i] == 'b') {
				int number = va_arg(more_args, int);
				_find_length(number, 2, "0b", &length);
			}
			else if(format[i] == 'x') {
				int number = va_arg(more_args, int);
				_find_length(number, 16, "0x", &length);
			}
			else if(format[i] == 's') {
				char* phrase = va_arg(more_args, char*);
				for(int j = 0; phrase[j] != '\0'; j++) {
					length++;
				}
			}
			else if(format[i] == 'c') {
				length++;
			}
			else if(format[i] == '%') {
				length++;
			}
			else if(format[i] == '$') {
				int number = va_arg(more_args, int);
				unsigned int absolute_value = number;

				if(number < 0) {
					length++;
					absolute_value = number * -1;
				}

				int quotient = absolute_value / 100;
				_find_length(quotient, 10,"$", &length);
				int remainder = absolute_value % 100;

				if(remainder < 10) {
					_find_length(remainder, 10, ".0", &length);
				}
				else {
					_find_length(remainder, 10, ".", &length);
				}
			}
			else {
				i--;
				length++;
			}
		}
		else {
			length++;
		}
	}
	va_end(more_args);

	va_start(more_args, format);

	char* final_string = malloc((sizeof(*final_string) * (length + 1)));
	printf("\n%d", length + 1);

	if (final_string != NULL) {
		char* temp = final_string;

		for(int i = 0; format[i] != '\0'; i++) {
			if(format[i] == '%') {
				i++;
				if(format[i] == 'd') {
					int number = va_arg(more_args, int);
					_to_string(number, 10, "", &temp);
				}
				else if(format[i] == 'b') {
					int number = va_arg(more_args, int);
					_to_string(number, 2, "0b", &temp);
				}
				else if(format[i] == 'x') {
					int number = va_arg(more_args, int);
					_to_string(number, 16, "0x", &temp);
				}
				else if(format[i] == 's') {
					char* phrase = va_arg(more_args, char*);
					for(int j = 0; phrase[j] != '\0'; j++) {
						(*temp) = phrase[j];
						temp++;
					}
				}
				else if(format[i] == 'c') {
					char alphabet = va_arg(more_args, int);
					(*temp) = alphabet;
					temp++;
				}
				else if(format[i] == '%') {
					(*temp) = '%';
					temp++;
				}
				else if(format[i] == '$') {
					int number = va_arg(more_args, int);
					unsigned int absolute_value = number;

					if(number < 0) {
						(*temp) = '-';
						temp++;
						absolute_value = number * -1;
					}

					int quotient = absolute_value / 100;
					_to_string(quotient, 10,"$", &temp);
					int remainder = absolute_value % 100;

					if(remainder < 10) {
						_to_string(remainder, 10, ".0", &temp);
					}
					else {
						_to_string(remainder, 10, ".", &temp);
					}
				}
				else {
					i--;
					(*temp) = format[i];
					temp++;
				}
			}
			else {
				(*temp) = format[i];
				temp++;
			}
		}	
		*temp = '\0';
		printf("temp: %s", temp);
		va_end(more_args);
	}
	return final_string;
}
