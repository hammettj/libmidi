#ifndef INCLUDE_MIDI_H_
#define INCLUDE_MIDI_H_

#include "mem_file.h"
#include <stdint.h>

typedef struct {
	uint16_t format;
	uint16_t ntracks;
	uint8_t timecode : 1;
	// if timecode = 0
	uint16_t ppqn;
} header_chunk;

typedef struct {
	mem_file* file;
	header_chunk header;
} midi;


midi* midi_open(const char* filename);
int midi_close(midi* midi);

#endif /* INCLUDE_MIDI_H_ */
