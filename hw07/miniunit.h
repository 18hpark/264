#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "clog.h"

#define mu_start() int __mu_first_failure_line_number = 0

#define mu_check(condition) \
do { \
	if((condition) == false && (__mu_first_failure_line_number == 0)) {\
		__mu_first_failure_line_number = __LINE__; \
	} \
} while(false)

#define mu_run(function) \
do { \
	if(function() == 0) { \
		logf_green("Test passed: %s\n", (#function)); \
	} \
	else { \
		logf_red("Test failed: %s at line %d\n", (#function), function()); \
	} \
} while(false)

#define mu_end() return __mu_first_failure_line_number

#define mu_check_strings_equal(s1, s2) mu_check(strcmp(s1, s2) == 0)

#endif
