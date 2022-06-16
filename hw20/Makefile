# VARIABLES
#
# CURRENT ASSIGNEMNT
ASG_NICKNAME	= HW20
BASE_NAME		= huffman
BASE_NAME_2		= priority_queue
BASE_NAME_3		= frequencies
BASE_NAME_4		= bit_writer
#
# EXECUTABLES
EXECUTABLE		= test_huffman
EXECUTABLE_GCOV	= $(EXECUTABLE)_gcov
#
# SOURCE FILENAMES
SRC_C			= $(BASE_NAME).c $(BASE_NAME_2).c $(BASE_NAME_3).c $(BASE_NAME_4).c
TEST_C			= test_$(BASE_NAME).c
SRC_H			= $(BASE_NAME).h $(BASE_NAME_2).h $(BASE_NAME_3).h $(BASE_NAME_4).h clog.h miniunit.h
SUBMIT_FILES	= $(SRC_C) $(SRC_H) $(TEST_C) Makefile
#
# SYSTEM
SHELL			= /bin/bash
CC				= gcc
CFLAGS			= -g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic 
CFLAGS_GCOV		= $(CFLAGS) -fprofile-arcs -ftest-coverage

#
# GCOV
#
# RULES
#
$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS)

test: $(EXECUTABLE) $(TEST_C)
	./$(EXECUTABLE)

clean: 
	rm -f $(EXECUTABLE) $(EXECUTABLE)_dbg $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno

pretest: submit
	264test $(ASG_NICKNAME)

submit:
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

valgrind: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE)

val_track: $(EXECUTABLE)
	valgrind --track-origins=yes ./$(EXECUTABLE)

coverage:
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

.PHONY: test pretest submit coverage clean valgrind
