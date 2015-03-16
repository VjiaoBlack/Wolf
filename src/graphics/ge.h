#ifndef GE_H
#define GE_H

#include <stdbool.h>

/*
 * ge.h
 * John Lekberg
 * The 3d engine used by our game.
 */

// The screen dimensions
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Creates a window and a screen to draw on.
bool init();

// Closes the graphics window
void close();

void drawTriangle(float *arr);

#endif
