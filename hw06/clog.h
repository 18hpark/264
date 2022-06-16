#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#ifndef NDEBUG
#define logf_ printf
#define logf_red(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[31m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define logf_green(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[32m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define logf_yellow(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[33m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define logf_blue(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[34m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define logf_magenta(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[35m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define logf_cyan(format, ...) \
do {\
	if (isatty(STDOUT_FILENO)) { \
		printf("\x1b[36m");\
		logf_(format, __VA_ARGS__);\
		printf("\x1b[0m"); \
		} \
	else { \
		logf_(format, __VA_ARGS__); \
		} \
} while(false)

#define log_int(n) printf("%s == %d\n", (#n), (n)) 
#define log_char(ch) printf("%s == '%c'\n", (#ch), (ch))
#define log_str(s) printf("%s == \"%s\"\n", (#s), (s))
#define log_addr(addr) printf("%s == %p\n", (#addr), ((void*)addr))
#define log_float(n) printf("%s == %.016f\n", (#n), (n))
#define log_bool(condition) \
do {\
	if ((condition) == false) { \
		printf("%s == false\n", (#condition)); \
	} \
	else { \
		printf("%s == true\n", (#condition)); \
	} \
} while(false)

#else
#define logf_(...)
#define logf_red(...)
#define logf_green(...)
#define logf_yellow(...)
#define logf_blue(...)
#define logf_magenta(...)
#define logf_cyan(...)
#define log_int(...)
#define log_char(...)
#define log_str(...)
#define log_addr(...)
#define log_float(...)
#define log_bool(...)
#endif /* end of include guard: NDEBUG */
