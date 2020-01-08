#include "midi.h"
#include "mem_file.h"
#include <stdlib.h>

midi* midi_open(const char* filename) {
	mem_file* file = mem_file_open(filename);
	if (!file) {
		return NULL;
	}

	// parse midi header
	if (read_uint8t(file) != 'M' || read_uint8t(file) != 'T' || read_uint8t(file) != 'h' || read_uint8t(file) != 'd') {
		mem_file_close(file);
		return NULL;
	}

	uint32_t len = read_uint32t(file);
	if (len != 6) { // length should be 6 bytes
		mem_file_close(file);
		return NULL;
	}

	midi* midi = malloc(sizeof(midi));
	midi->file = file;
	midi->header.format = read_uint16t(file);
	midi->header.ntracks = read_uint16t(file);

	uint16_t tickdiv = read_uint16t(file);

	if (tickdiv & (1 << 15)) {
		// fixme not supported yet..
		mem_file_close(file);
		free(midi);

		return NULL;
	} else {
		midi->header.timecode = 0;
		midi->header.ppqn = tickdiv >> 1;
	}

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
