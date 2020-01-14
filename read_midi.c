#include <stdio.h>
#include <stdlib.h>
#include "midi.h"

int main(int argc, char** argv) {
	midi* midi = NULL;
	if ((midi = midi_open("super-mario.mid"))) {
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

			for (midi_event* event = track.midi_event; event->next; event = event->next) {
				printf("%u\t : type: %.3u\n", event->delta_time, event->type);
			}

			printf("\n");
		}


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
