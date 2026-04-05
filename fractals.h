#ifndef _FRACTALS_H_
#define _FRACTALS_H_

#include <raylib.h>

typedef struct {
	Vector2 p1;
	Vector2 p2;
} line_segment_t;

typedef void (*genericLineMapper) (line_segment_t*);

void mapLine(line_segment_t* segment, genericLineMapper mapper);

void heighwayMap1(line_segment_t* line);
void heighwayMap2(line_segment_t* line);

#endif
