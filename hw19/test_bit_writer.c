#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "bit_writer.h"
#include "miniunit.h"

/*
static bool _check_file_contents(char const* path, size_t num_bytes, uint8_t const* bytes) {
	FILE* fp = fopen(path, "r");
	for (int i = 0; i < num_bytes; i++) {
		if (fgetc(fp) != bytes[i]) {
			fclose(fp);
		}
	}
	fclose(fp);
	return true;
}
*/

static int _test_case_1() {
	mu_start();
	BitWriter writer = open_bit_writer("new_files.bits");
	write_bits(&writer, 0x05, 3);
	write_bits(&writer, 0xf3, 3);
	write_bits(&writer, 0x01, 2);
	write_bits(&writer, 0x20, 6);
	write_bits(&writer, 0x13, 5);

	mu_check(writer.current_byte == 0x60);
	mu_check(writer.num_bits_left == 5);

	close_bit_writer(&writer);

	//bool is_success = _check_file_contents("new_files.bits", 2, (uint8_t[]){0xad,0x82});
	//mu_check(is_success);
	mu_end();
}


int main(int argc, char* argv[]) {

	mu_run(_test_case_1);
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
