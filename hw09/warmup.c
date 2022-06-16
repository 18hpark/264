 /* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include <stdio.h>
#include <stdlib.h>

char* my_strdup(const char* original) {
	int length = 1;   			// NULL needs to be detected all cases 
	for (int j = 0; original[j] != '\0'; ++j) {
		length += 1;
	}
	char* locate = malloc(sizeof(*locate) * length);
	for (int i = 0; i < length; i++) {
		locate[i] = original[i];
	}
	return locate;
}

int main(int argc, char *argv[]) {
	char s[] = "abc\n";
	fputs(s, stdout);  // Should print "abc" followed by a newline ('\n')

	char* t = my_strdup(s);
	fputs(t, stdout);  // Should print "abc" followed by a newline ('\n')
	free(t);

	return EXIT_SUCCESS;
}
