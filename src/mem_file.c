#include "mem_file.h"
#include <stdlib.h>
#include <stdio.h>

mem_file* mem_file_open(const char* filename) {
	mem_file* file = malloc(sizeof(mem_file));

	FILE* fp = fopen(filename, "rb");
	if (!fseek(fp, 0, SEEK_END)) {
		file->len = ftell(fp);
		if (!fseek(fp, 0, SEEK_SET)) {
			file->data = malloc(sizeof(uint8_t) * file->len);
			if (fread(file->data, sizeof(uint8_t), file->len, fp) == file->len) {
				return file;
			}
		}
	}
	return NULL;
}

int mem_file_close(mem_file* file) {
	if (file) {
		free(file->data);
		free(file);
		file = NULL;
	}
	return 1;
}
