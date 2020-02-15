#include "byte_buffer.h"
#include "midi.h"
#include <stdlib.h>

#define TYPE_END_OF_TRACK (0x2F)

track_chunk* read_track_chunk(track_chunk* chunk, byte_buffer* buf);

midi* midi_open(byte_buffer* buf) {
	// parse midi header
	if (read_uint8t(buf) == 'M' && read_uint8t(buf) == 'T' && read_uint8t(buf) == 'h' && read_uint8t(buf) == 'd') {
		uint32_t len = read_uint32t(buf);
		if (len == 6) { // length should be 6 bytes
			midi* midi = malloc(sizeof(midi));
			if (midi) {
				midi->header.format = read_uint16t(buf);
				uint16_t ntracks = read_uint16t(buf);
				midi->header.ntracks = ntracks;

				uint16_t tickdiv = read_uint16t(buf);
				if (~tickdiv & (1 << 15)) {
					midi->header.timecode = 0;
					midi->header.ppqn = tickdiv >> 1;

					midi->track_chunks = malloc(sizeof(track_chunk) * ntracks);
					if (midi->track_chunks) {
						for (uint16_t i = 0; i < ntracks; ++i) {
							read_track_chunk(&midi->track_chunks[i], buf);
						}
						return midi;
					}
				}

				free(midi);
			}
		}
	}

	return NULL;
}

uint32_t read_var_length(byte_buffer* buf) {
	uint32_t n = 0;
	do {
		uint8_t tmp = read_uint8t(buf);

		// last bit is set..
		if (tmp & 1 << 7) {
				n += (tmp & 127);
				n <<= 7;
		} else {
				return n + tmp;
		}
	} while (1);
}

midi_event* next_event(byte_buffer* buf) {
	midi_event* event = malloc(sizeof(midi_event));
	if (event) {
		event->delta_time = read_var_length(buf);
		event->type = read_uint8t(buf);
		event->meta_type = 0;
		event->len = 0;
		event->data = NULL;
		event->next = NULL;

		switch (event->type & 0xF0) {
			case TYPE_NOTE_OFF:
			case TYPE_NOTE_ON:
			case TYPE_POLYPHONIC_PRESSURE:
			case TYPE_CONTROL_CHANGE:
			case TYPE_PITCH_BEND:
				{
					event->len = 2;
					if ((event->data = malloc(sizeof(uint8_t) * event->len))) {
						read(event->data, buf, event->len);
						return event;
					}
					break;
				}
			case TYPE_PROGRAM_CHANGE:
			case TYPE_CHANNEL_PRESSURE:
				{
					event->len = 1;
					if ((event->data = malloc(sizeof(uint8_t) * event->len))) {
						read(event->data, buf, event->len);
						return event;
					}
					break;
				}
			case 0xF0:
				{
					switch(event->type) {
						case TYPE_SYSEX:
						case TYPE_SYSEX2:
							{
								event->len = read_var_length(buf);
								if ((event->data = malloc(sizeof(uint8_t) * event->len))) {
									read(event->data, buf, event->len);
									return event;
								}
								break;
							}
						case TYPE_META:
							{
								event->meta_type = read_uint8t(buf);
								event->len = read_var_length(buf);
								if (!event->len) return event;

								if ((event->data = malloc(sizeof(uint8_t) * event->len))) {
									read(event->data, buf, event->len);
									return event;
								}
								break;
							}
					}
					break;
				}
		}
		free(event);
	}
	return NULL;
}

track_chunk* read_track_chunk(track_chunk* chunk, byte_buffer* buf) {
	read(chunk->id, buf, 4);
	chunk->len = read_uint32t(buf);

	midi_event* last_event = next_event(buf);
	if (!last_event) return NULL;

	chunk->midi_event = last_event;
	while (last_event->meta_type ^ TYPE_END_OF_TRACK) {
		midi_event* event = next_event(buf);
		if (!event) return NULL;

		last_event->next = event;
		last_event = event;
	}

	return chunk;
}

int midi_close(midi* midi) {
	if (midi) {
		for (uint16_t i = 0; i < midi->header.ntracks; ++i) {
			track_chunk track = midi->track_chunks[i];

			midi_event* event = track.midi_event;
			while (event) {
				midi_event* next = event->next;
				free(event->data);
				free(event);
				event = next;
			}
		}

		free(midi->track_chunks);
		free(midi);
		midi = NULL;
	}

	return 1;
}
