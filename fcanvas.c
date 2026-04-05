#include "fcanvas.h"
#include <stdlib.h>

int initAppHeighway(fractal_app_t* fa)
{
	fa->lineCount = 1;
	fa->freeIndex = 1;
	size_t reqd = sizeof(line_segment_t) * 256;
	fa->lineData = malloc(reqd);
	if (fa->lineData == NULL) return -1;
	fa->bytesAllocated = reqd;

	fa->lineData[0].p1 = (Vector2){0.0f, 0.0f};
	fa->lineData[0].p2 = (Vector2){1.0f, 0.0f};

	InitWindow(1600, 1200, "Heighway Dragon");
	fa->canvas = GenImageColor(1600, 1200, RAYWHITE);
	return 0;
}

size_t getRemainingSpace(fractal_app_t* fa)
{
	return fa->bytesAllocated - sizeof(line_segment_t) * fa->lineCount;
}


int updateHeighway(fractal_app_t* fa)
{
	if (IsKeyPressed(KEY_RIGHT)) {
		size_t remaminingSpace = getRemainingSpace(fa);
		if (remaminingSpace < sizeof(line_segment_t) * fa->lineCount)
		{
			fa->bytesAllocated *= 4;
			fa->lineData = realloc(fa->lineData, fa->bytesAllocated);
			if (fa->lineData == NULL) return -1;
		}
		unsigned int oldCount = fa->lineCount;
		fa->freeIndex = oldCount;
		for(unsigned int i = 0; i < oldCount; i++)
		{
			int dupIdx = dupLine(fa, i);
			mapLine(fa->lineData + i, heighwayMap1);
			mapLine(fa->lineData + dupIdx, heighwayMap2);
		}
		fa->lineCount = oldCount * 2;
	}

	BeginDrawing();
	ClearBackground(BLACK);
	drawHeighway(fa);
	EndDrawing();
	return 0;
}

void drawHeighway(fractal_app_t* fa)
{
	float minX = 1e9f, minY = 1e9f, maxX = -1e9f, maxY = -1e9f;
	for (unsigned int i = 0; i < fa->lineCount; i++) {
		line_segment_t* s = &fa->lineData[i];
		if (s->p1.x < minX) minX = s->p1.x;
		if (s->p1.y < minY) minY = s->p1.y;
		if (s->p2.x < minX) minX = s->p2.x;
		if (s->p2.y < minY) minY = s->p2.y;
		if (s->p1.x > maxX) maxX = s->p1.x;
		if (s->p1.y > maxY) maxY = s->p1.y;
		if (s->p2.x > maxX) maxX = s->p2.x;
		if (s->p2.y > maxY) maxY = s->p2.y;
	}

	float fw = maxX - minX;
	float fh = maxY - minY;
	if (fw < 1e-6f) fw = 1.0f;
	if (fh < 1e-6f) fh = 1.0f;

	int screenW = GetScreenWidth();
	int screenH = GetScreenHeight();
	float margin = 40.0f;
	float scaleX = (screenW - 2 * margin) / fw;
	float scaleY = (screenH - 2 * margin) / fh;
	float scale = (scaleX < scaleY) ? scaleX : scaleY;

	float offX = margin + ((screenW - 2 * margin) - fw * scale) / 2.0f - minX * scale;
	float offY = margin + ((screenH - 2 * margin) - fh * scale) / 2.0f - minY * scale;

	for (unsigned int i = 0; i < fa->lineCount; i++) {
		line_segment_t* s = &fa->lineData[i];
		Vector2 a = {s->p1.x * scale + offX, s->p1.y * scale + offY};
		Vector2 b = {s->p2.x * scale + offX, s->p2.y * scale + offY};
		DrawLineV(a, b, RAYWHITE);
	}
}

int dupLine(fractal_app_t* fa, int index)
{
	int idx = fa->freeIndex;
	*(fa->lineData + idx) = *(fa->lineData + index);
	fa->freeIndex++;
	return idx;
}

void cleanupApp(fractal_app_t* fa)
{
	free(fa->lineData);
}
