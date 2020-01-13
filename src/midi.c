#include "byte_buffer.h"
#include "midi.h"
#include <stdlib.h>

void read_track_chunk(track_chunk* chunk, byte_buffer* buf);

midi* midi_open(const char* filename) {
	byte_buffer* buf = byte_buffer_from_file(filename);
	if (!buf) {
		return NULL;
	}

	// parse midi header
	if (read_uint8t(buf) != 'M' || read_uint8t(buf) != 'T' || read_uint8t(buf) != 'h' || read_uint8t(buf) != 'd') {
		byte_buffer_dispose(buf);
		return NULL;
	}

	uint32_t len = read_uint32t(buf);
	if (len != 6) { // length should be 6 bytes
		byte_buffer_dispose(buf);
		return NULL;
	}

	midi* midi = malloc(sizeof(midi));
	midi->buf = buf;
	midi->header.format = read_uint16t(buf);
	uint16_t ntracks = read_uint16t(buf);
	midi->header.ntracks = ntracks;

	uint16_t tickdiv = read_uint16t(buf);
	if (tickdiv & (1 << 15)) {
		// fixme not supported yet..
		byte_buffer_dispose(buf);
		free(midi);

		return NULL;
	} else {
		midi->header.timecode = 0;
		midi->header.ppqn = tickdiv >> 1;
	}

	midi->track_chunks = malloc(sizeof(track_chunk) * ntracks);
	for (uint16_t i = 0; i < ntracks; ++i) {
		read_track_chunk(&midi->track_chunks[i], midi->buf);
	}

	return midi;
}

void read_track_chunk(track_chunk* chunk, byte_buffer* buf) {
	read(chunk->id, buf, 4);
	uint32_t len = read_uint32t(buf);
	chunk->len = len;
	chunk->data = malloc(sizeof(uint8_t) * len);
	read(chunk->data, buf, len);
}

int midi_close(midi* midi) {
	if (midi) {
		byte_buffer_dispose(midi->buf);
		free(midi);
		midi = NULL;
	}

	return 1;
}
