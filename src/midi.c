#include "midi.h"
#include <stdio.h>
#include <stdlib.h>

midi* midi_open(const char* filename) {
	midi* midi = malloc(sizeof(midi));

	FILE* fp = fopen(filename, "rb");
	if (!fseek(fp, 0, SEEK_END)) {
		midi->len = ftell(fp);
		if (!fseek(fp, 0, SEEK_SET)) {
			midi->data = malloc(sizeof(uint8_t) * midi->len);
			if (fread(midi->data, sizeof(uint8_t), midi->len, fp) == midi->len) {
				return midi;
			}
		}
	}

	return NULL;
}

int midi_close(midi* midi) {
	if (midi) {
		free(midi->data);
		free(midi);
	}

	return 1;
}
