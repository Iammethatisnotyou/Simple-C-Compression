/* SCC - Simple C Compression */

char *run_length_encoding(const char *file, bool compression);
char *run_length_compression(unsigned int size, char *current_str, char *new_str);
char *run_length_decompression(unsigned int size, char *current_str, char *new_str);
