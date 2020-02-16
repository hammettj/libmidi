#ifndef INCLUDE_MIDI_H_
#define INCLUDE_MIDI_H_

#include <stdint.h>
#include "byte_buffer.h"

#define TYPE_META					(0xFF)
#define TYPE_SYSEX					(0xF0)
#define TYPE_SYSEX2					(0xF7)
#define TYPE_NOTE_OFF				(0x80)
#define TYPE_NOTE_ON				(0x90)
#define TYPE_POLYPHONIC_PRESSURE	(0xA0)
#define TYPE_CONTROL_CHANGE			(0xB0)
#define TYPE_PROGRAM_CHANGE			(0xC0)
#define TYPE_CHANNEL_PRESSURE		(0xD0)
#define TYPE_PITCH_BEND				(0xE0)

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


midi* midi_load(byte_buffer* buf);
int midi_dispose(midi* midi);

#endif /* INCLUDE_MIDI_H_ */
