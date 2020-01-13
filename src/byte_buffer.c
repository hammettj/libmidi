#include "../include/byte_buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <endian.h>

byte_buffer* byte_buffer_from_file(const char* filename) {
	byte_buffer* file = malloc(sizeof(byte_buffer));

	FILE* fp = fopen(filename, "rb");
	if (!fseek(fp, 0, SEEK_END)) {
		file->len = ftell(fp);
		if (!fseek(fp, 0, SEEK_SET)) {
			file->data = malloc(sizeof(uint8_t) * file->len);
			if (fread(file->data, sizeof(uint8_t), file->len, fp) == file->len) {
				fclose(fp);
				return file;
			}
		}
	}

	fclose(fp);
	return NULL;
}

int byte_buffer_dispose(byte_buffer* buf) {
	if (buf) {
		free(buf->data);
		free(buf);
		buf = NULL;
	}
	return 1;
}

uint8_t read_uint8t(byte_buffer* buf) {
	return buf->data[buf->pos++];
}

uint16_t read_uint16t(byte_buffer* buf) {
	return htobe16(
			  buf->data[buf->pos++]
			| buf->data[buf->pos++] << 8
	);
}

uint32_t read_uint32t(byte_buffer* buf) {
	return htobe32(
			  buf->data[buf->pos++]
			| buf->data[buf->pos++] << 8
			| buf->data[buf->pos++] << 16
			| buf->data[buf->pos++] << 24
	);
}
