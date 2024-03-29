#include "../include/byte_buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct byte_buffer {
	size_t pos;
	size_t len;
	uint8_t* data;
};

uint16_t be16(uint16_t x);
uint32_t be32(uint32_t x);

byte_buffer* byte_buffer_from_file(const char* filename) {
	byte_buffer* buf = malloc(sizeof(byte_buffer));
	if (buf) {
		buf->data = NULL;

		FILE* fp = fopen(filename, "rb");
		if (fp) {
			if (!fseek(fp, 0, SEEK_END)) {
				buf->len = ftell(fp);
				if (!fseek(fp, 0, SEEK_SET)) {
					buf->data = malloc(sizeof(uint8_t) * buf->len);
					if (buf->data) {
						if (fread(buf->data, sizeof(uint8_t), buf->len, fp) == buf->len) {
							fclose(fp);
							return buf;
						}
					}
				}
			}
			fclose(fp);
		}
		byte_buffer_dispose(buf);
	}
	return NULL;
}

byte_buffer* byte_buffer_from_array(const uint8_t* array, size_t size) {
	byte_buffer* buf = malloc(sizeof(byte_buffer));
	if (buf) {
		if ((buf->data = malloc(size))) {
			memcpy(buf->data, array, size);
			buf->len = size;

			return buf;
		}
		byte_buffer_dispose(buf);
	}
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
	return be16(
			  buf->data[buf->pos++]
			| buf->data[buf->pos++] << 8
	);
}

uint32_t read_uint32t(byte_buffer* buf) {
	return be32(
			  buf->data[buf->pos++]
			| buf->data[buf->pos++] << 8
			| buf->data[buf->pos++] << 16
			| buf->data[buf->pos++] << 24
	);
}

size_t read(uint8_t* to, byte_buffer* from, size_t n) {
	size_t i = 0;
	for (; i < n; ++i) {
		to[i] = read_uint8t(from);
	}
	return i;
}

uint16_t be16(uint16_t x) {
	if (__BYTE_ORDER == __LITTLE_ENDIAN) {
		return (((((x) >> 8) & 0xff) | (((x) & 0xff) << 8)));
	}
	return x;
}

uint32_t be32(uint32_t x) {
	if (__BYTE_ORDER == __LITTLE_ENDIAN) {
		return ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >> 8) | (((x) & 0x0000ff00u) << 8) | (((x) & 0x000000ffu) << 24));
	}
	return x;
}
