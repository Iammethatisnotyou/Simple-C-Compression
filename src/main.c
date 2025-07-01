/* SCC - Simple C Compression */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "algorithms/run_length.h"
#include "util.h"

char *run_length_encoding(char *file, bool compression);
void file_creation(char *contents, bool compression);

char *run_length_encoding(char *file, bool compression) {
	FILE *fptr = fopen(file, "r");
	if (fptr == NULL) invalid_file();

	int ch;
	unsigned int size = 0;

	char *new_str = malloc(1);
	while ((ch = fgetc(fptr)) != EOF) size++;
	rewind(fptr);

	char *current_str = malloc(size + 1);
	fread(current_str, sizeof(char), size, fptr);
	current_str[size++] = '\0';

	if (compression) new_str = run_length_compression(size, current_str, new_str);
	else new_str = run_length_decompression(size, current_str, new_str);

	fclose(fptr);
	free(current_str);
	return new_str;
}
void file_creation(char *contents, bool compression) {
	char *file_zip = malloc(1);
	char *current_str;
	malloc_check(file_zip);
	file_zip[0] = '\0';

	for (size_t i = 0; i < strlen(contents); i++) {
		if (contents[i] == '.') break;

		file_zip = realloc(file_zip, strlen(file_zip) + 2);
		malloc_check(file_zip);

		char temporary[2] = { contents[i], '\0' };
		strncat(file_zip, temporary, 2);
	}
	file_zip = realloc(file_zip, strlen(file_zip) + 5 + 1);

	if (compression) strcat(file_zip, ".vip");
	else strcat(file_zip, ".txt");

	malloc_check(file_zip);
	FILE *fptr = fopen(file_zip, "w");
	if (fptr == NULL) invalid_file();

	current_str = run_length_encoding(contents, compression);

	fwrite(current_str, sizeof(char), strlen(current_str), fptr);
	fclose(fptr);
}
int main(int argc, char *argv[]) {
	if (argc != 3) die("Too many arguments / Not enough:");
	else if (strcmp(argv[1], "-h") == 0) die("For help check the man page or the README.:");

	else if (strcmp(argv[1], "-rc") == 0) file_creation(argv[2], true);
	else if (strcmp(argv[1], "-rd") == 0) file_creation(argv[2], false);

	else die("Invalid use, check man page or README:");
}
