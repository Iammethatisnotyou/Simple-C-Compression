#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../util.h"

#define MAX_SIZE 2056 /* TODO Change snprintf size later */

char *run_length_compression(unsigned int size, char *current_str, char *new_str) {
	unsigned int char_amount = 1, out_i = 0, j = 0;
	for (j = 1; j < size; j++) {
		if (current_str[j] == current_str[j - 1]) { char_amount++;

		} else {
			new_str = realloc(new_str, strlen(new_str) + 4);
			malloc_check(new_str);
			out_i       += sprintf(new_str + out_i, "%c%d", current_str[j - 1], char_amount);
			char_amount  = 1;
		}
	}
	new_str[++out_i] = '\0';
	return new_str;
}
char *run_length_decompression(unsigned int size, char *current_str, char *new_str) {
	unsigned int out_i = 0, j = 1;
	for (; j < size; j++) {
		if (isdigit(current_str[j])) {
			const int num      = current_str[j] - '0';
			const char last_ch = current_str[j - 1];

			new_str = realloc(new_str, strlen(new_str) + num + 1);
			malloc_check(new_str);

			for (int k = 0; k < num; k++) {
				new_str[out_i + k] = last_ch;
			}
			out_i += num;
		} else {
			new_str = realloc(new_str, strlen(new_str) + 12);
			malloc_check(new_str);
		}
	}
	new_str[++out_i] = '\0';
	return new_str;
}
