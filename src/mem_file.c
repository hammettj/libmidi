#include "mem_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <endian.h>

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

uint8_t read_uint8t(mem_file* file) {
	return file->data[file->pos++];
}

uint16_t read_uint16t(mem_file* file) {
	return htobe16(
			  file->data[file->pos++]
			| file->data[file->pos++] << 8
	);
}

uint32_t read_uint32t(mem_file* file) {
	return htobe32(
			  file->data[file->pos++]
			| file->data[file->pos++] << 8
			| file->data[file->pos++] << 16
			| file->data[file->pos++] << 24
	);
}
