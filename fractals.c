#include "fractals.h"

void mapLine(line_segment_t* segment, genericLineMapper mapper)
{
	mapper(segment);
}

void heighwayMap1(line_segment_t* line)
{
	float x1 = line->p1.x, y1 = line->p1.y;
	float x2 = line->p2.x, y2 = line->p2.y;
	line->p1.x = (x1 - y1) / 2;
	line->p1.y = (x1 + y1) / 2;
	line->p2.x = (x2 - y2) / 2;
	line->p2.y = (x2 + y2) / 2;
}

void heighwayMap2(line_segment_t* line)
{
	float x1 = line->p1.x, y1 = line->p1.y;
	float x2 = line->p2.x, y2 = line->p2.y;
	line->p1.x = (2 - x1 - y1) / 2;
	line->p1.y = (x1 - y1) / 2;
	line->p2.x = (2 - x2 - y2) / 2;
	line->p2.y = (x2 - y2) / 2;
}
