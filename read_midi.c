#include <stdio.h>
#include <stdlib.h>
#include "midi.h"

int main(int argc, char** argv) {
	byte_buffer* buf = byte_buffer_from_file("super-mario.mid");
	if (!buf) {
		printf("could not load file!\n");
		return 1;
	}

	midi* midi = NULL;
	if ((midi = midi_open(buf))) {
		printf("MIDI file opened!\n");

		printf("format: %u\n", midi->header.format);
		printf("ntracks: %u\n", midi->header.ntracks);
		printf("timecode: %u\n", midi->header.timecode);
		printf("ppqn: %u\n", midi->header.ppqn);
		printf("\n");

		for (int i = 0; i < midi->header.ntracks; ++i) {
			track_chunk track = midi->track_chunks[i];
			printf("id: %.4s\n", track.id);
			printf("len: %u\n", track.len);

			for (midi_event* event = track.midi_event; event != NULL; event = event->next) {
				printf("%u\t : type: 0x%02X \t meta_type: 0x%02X\n", event->delta_time, event->type, event->meta_type);
			}

			printf("\n");
		}

		byte_buffer_dispose(buf);
		if (midi_close(midi)) {
			printf("MIDI file closed!\n");
		} else {
			printf("error closing MIDI file!\n");
			return 1;
		}
	} else {
		printf("error opening MIDI file!\n");
		return 1;
	}

	return 0;
}
