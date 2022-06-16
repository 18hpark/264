#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include "frequencies.h"

bool calc_frequencies(Frequencies freqs, const char* path, const char** a_error) {
	FILE* fp = fopen(path, "r");
	if (fp == NULL) {
		*a_error = strerror(errno);
		return false;
	}
	else {
		for(int ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
			freqs[ch] += 1;
		}
	}
	fclose(fp);	
	return true;
}
