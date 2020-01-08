#include "midi.h"

FILE* midi_open(const char* filename) {
	return fopen(filename, "r");
}

int midi_close(FILE* fp) {
	if (!fclose(fp)) {
		fp = NULL;
		return 1;
	}
	return 0;
}
