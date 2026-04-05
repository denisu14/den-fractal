#include <stdio.h>
#include <raylib.h>
#include "fcanvas.h"

int
main(void)
{
	fractal_app_t fractalApp;
	if (initAppHeighway(&fractalApp) < 0) {
		fprintf(stderr, "Failed to initialize\n");
		return 1;
	}

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		updateHeighway(&fractalApp);
	}

	cleanupApp(&fractalApp);
	return 0;
}
