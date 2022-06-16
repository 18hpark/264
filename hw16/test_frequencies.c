#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "frequencies.h"
#include "miniunit.h"
#include "clog.h"

/*void _print_frequencies(Frequencies freqs) {
	for (int i = 0; i < 256; i++) {
		printf("[%d] [%c]: %ld\n", i, i, freqs[i]);
	}
}*/

const char* _write_file(const char* contents, const char* filename) {
	FILE* fp = fopen(filename, "w");
	fputs(contents, fp);
	fclose(fp);
	return filename;
}

static int _test_one() {
	mu_start();
	Frequencies freqs_one = {0};
	const char* path = _write_file("valid test case", "valid_test.txt");
	const char* a_error = NULL;
	bool is_success = calc_frequencies(freqs_one, path, &a_error);
	mu_check(is_success);
	//_print_frequencies(freqs_one);
	mu_end();
}

static int _test_two() {
	mu_start();
	Frequencies freqs_two = {0};
	char const* path = "invalid_test.txt";
	char const* a_error = NULL;
	bool is_success = calc_frequencies(freqs_two, path, &a_error);
	mu_check(!is_success);
	//_print_frequencies(freqs_one);
	mu_end();
}
	
int main(int argc, char* argv[]) {
	mu_run(_test_one);
	mu_run(_test_two);
	return EXIT_SUCCESS;
}
