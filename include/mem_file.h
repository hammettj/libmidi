#ifndef INCLUDE_MEM_FILE_H_
#define INCLUDE_MEM_FILE_H_

#include <stdint.h>
#include <stddef.h>

typedef struct {
	size_t pos;
	size_t len;
	uint8_t* data;
} mem_file;

mem_file* mem_file_open(const char* filename);
int mem_file_close(mem_file* file);

#endif /* INCLUDE_MEM_FILE_H_ */
