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
