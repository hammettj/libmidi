#ifndef INCLUDE_MIDI_H_
#define INCLUDE_MIDI_H_

#include <stdint.h>
#include "byte_buffer.h"

typedef struct {
	uint16_t format;
	uint16_t ntracks;
	uint8_t timecode : 1;
	// if timecode = 0
	uint16_t ppqn;
} header_chunk;

typedef struct {
	byte_buffer* buf;
	header_chunk header;
} midi;


midi* midi_open(const char* filename);
int midi_close(midi* midi);

#endif /* INCLUDE_MIDI_H_ */
