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

char *run_length_encoding(const char *file, bool compression);
void file_creation(char *contents, bool compression);
void write_to_file(const char *file, const char *contents);

char *run_length_encoding(const char *file, bool compression) {
	FILE *fptr = fopen(file, "r");
	if (fptr == NULL) invalid_file();

	int ch;
	unsigned int size = 0;

	char *run_str = malloc(1);
	while ((ch = fgetc(fptr)) != EOF) size++;
	rewind(fptr);

	char *tmp_str = malloc(size + 1);
	fread(tmp_str, sizeof(char), size, fptr);
	tmp_str[size++] = '\0';

	if (compression) run_str = run_length_compression(size, tmp_str, run_str);
	else run_str = run_length_decompression(size, tmp_str, run_str);

	fclose(fptr);
	free(tmp_str);
	return run_str;
}
void file_creation(char *contents, bool compression) {
	char *file_zip = malloc(1);
	malloc_check(file_zip);
	file_zip[0] = '\0';

	for (size_t i = 0; i < strlen(contents); i++) {
		if (contents[i] == '.') break;

		file_zip = realloc(file_zip, strlen(file_zip) + 2);
		malloc_check(file_zip);

		const char temporary[2] = {contents[i], '\0'};
		strncat(file_zip, temporary, 2);
	}
	file_zip = realloc(file_zip, strlen(file_zip) + 6);

	if (compression) strcat(file_zip, ".vip");
	else strcat(file_zip, ".txt");

	malloc_check(file_zip);
	const char *file_contents = run_length_encoding(contents, compression);
	write_to_file(file_zip, file_contents);
}
void write_to_file(const char *file, const char *contents) {
	FILE *fptr = fopen(file, "w");
	if (fptr == NULL) invalid_file();

	fwrite(contents, sizeof(char), strlen(contents), fptr);
	fclose(fptr);
}
int main(int argc, char *argv[]) {
	if (argc != 3) die("Too many arguments / Not enough:");
	else if (strcmp(argv[1], "-h") == 0) die("For help check the man page or the README.:");

	else if (strcmp(argv[1], "-rc") == 0) file_creation(argv[2], true);
	else if (strcmp(argv[1], "-rd") == 0) file_creation(argv[2], false);

	else die("Invalid use, check man page or README:");
}
