#ifndef INCLUDE_BYTE_BUFFER_H_
#define INCLUDE_BYTE_BUFFER_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
	size_t pos;
	size_t len;
	uint8_t* data;
} byte_buffer;

byte_buffer* byte_buffer_from_file(const char* filename);
int byte_buffer_dispose(byte_buffer* buf);

uint8_t read_uint8t(byte_buffer* buf);
uint16_t read_uint16t(byte_buffer* buf);
uint32_t read_uint32t(byte_buffer* buf);

#endif /* INCLUDE_BYTE_BUFFER_H_ */