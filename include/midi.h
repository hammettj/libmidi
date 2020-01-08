#ifndef INCLUDE_MIDI_H_
#define INCLUDE_MIDI_H_

#include <stdio.h>

FILE* midi_open(const char* filename);
int midi_close(FILE* fp);

#endif /* INCLUDE_MIDI_H_ */
