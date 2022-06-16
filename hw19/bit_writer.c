#include <assert.h>
#include "bit_writer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

BitWriter open_bit_writer(const char* path) {
	return (BitWriter) { .file = fopen(path, "wb"), .current_byte = 0, .num_bits_left = 8 };
}

void write_bits(BitWriter* a_writer, uint8_t bits, uint8_t num_bits_to_write) {
	
	assert(num_bits_to_write >= 0 && num_bits_to_write <= 8);
	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);
	
	//if no enough room
	if (num_bits_to_write > (a_writer -> num_bits_left)) {
		(a_writer -> current_byte) |= (bits >> (num_bits_to_write - (a_writer -> num_bits_left))); 
		num_bits_to_write = num_bits_to_write - (a_writer -> num_bits_left); //update num bits to write
		bits = bits << (8 - num_bits_to_write);	//put bits with updated num bits to write
		a_writer -> num_bits_left = 0; //since there's no room anymore num_bits_left = 0
		flush_bit_writer(a_writer); //clear
	}
	else {	
		(a_writer -> current_byte) |= (bits << (a_writer -> num_bits_left - num_bits_to_write)); //put bits w num bits to write
		(a_writer -> num_bits_left) = (a_writer -> num_bits_left) - num_bits_to_write; // update num bits left
		num_bits_to_write = 0; //update num bits to write = 0 since it was all used
		//if there no room clear it
		if (a_writer -> num_bits_left == 0) {
			flush_bit_writer(a_writer);
		}
	}
	if (num_bits_to_write > 0) {
		a_writer -> current_byte += bits;
		a_writer -> num_bits_left -= num_bits_to_write;
	}
	assert(a_writer -> num_bits_left >= 1 && a_writer -> num_bits_left <= 8);
}

void flush_bit_writer(BitWriter* a_writer) {
	if (a_writer -> num_bits_left != 8) {
		fputc(a_writer -> current_byte, a_writer -> file);
		a_writer -> current_byte = 0;
		a_writer -> num_bits_left = 8;
	}
}

void close_bit_writer(BitWriter* a_writer) {
	flush_bit_writer(a_writer);
	fclose(a_writer -> file);
	a_writer -> file = NULL;
}

#define __BIT_WRITER_C_V1__
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab colorcolumn=96: */
