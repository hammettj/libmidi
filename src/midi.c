#include "midi.h"
#include "mem_file.h"
#include <stdlib.h>

midi* midi_open(const char* filename) {
	mem_file* file = mem_file_open(filename);
	if (!file) {
		return NULL;
	}

	midi* midi = malloc(sizeof(midi));
	midi->file = file;

	return midi;
}

int midi_close(midi* midi) {
	if (midi) {
		mem_file_close(midi->file);
		free(midi);
		midi = NULL;
	}

	return 1;
}
