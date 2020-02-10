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

typedef struct midi_event {
	uint32_t delta_time;
	uint8_t type;
	uint32_t len;
	uint8_t* data;
	uint8_t meta_type;
	struct midi_event* next;
} midi_event;

typedef struct {
	uint8_t id[4];
	uint32_t len;
	midi_event* midi_event;
} track_chunk;

typedef struct {
	header_chunk header;
	track_chunk* track_chunks;
} midi;


midi* midi_open(const char* filename);
int midi_close(midi* midi);

#endif /* INCLUDE_MIDI_H_ */
