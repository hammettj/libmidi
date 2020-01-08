#include "midi.h"
#include <stdlib.h>

midi* midi_open(const char* filename) {
	midi* midi = malloc(sizeof(midi));
	midi->fp = fopen(filename, "r");
	if (midi->fp) {
		return midi;
	}

	return NULL;
}

int midi_close(midi* midi) {
	if (midi) {
		fclose(midi->fp);
		free(midi);
	}

	return 1;
}
