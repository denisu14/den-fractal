#ifndef _FCANVAS_H_
#define _FCANVAS_H_

#include <raylib.h>
#include <stddef.h>
#include "fractals.h"

typedef Image fractalcanvas_t;

typedef struct {
	unsigned int lineCount;
	line_segment_t* lineData;
	int freeIndex; 
	size_t bytesAllocated;
	fractalcanvas_t canvas;
} fractal_app_t;

int initAppHeighway(fractal_app_t* fa);

size_t getRemainingSpace(fractal_app_t* fa);

int dupLine(fractal_app_t* fa, int index);

void drawHeighway(fractal_app_t* fa);
int updateHeighway(fractal_app_t* fa);
void cleanupApp(fractal_app_t* fa);

#endif
