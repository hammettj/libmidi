#include <stdio.h>
#include <stdlib.h>
#include "midi.h"

int main(int argc, char** argv) {
	FILE* fp = NULL;
	if ((fp = midi_open("super-mario.mid"))) {
		printf("MIDI file opened!\n");
		if (midi_close(fp)) {
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
