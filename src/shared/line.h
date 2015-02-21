#ifndef LINE_H
#define LINE_H

#include "vector2.h"

typedef struct line {
    vector2* position1;
    vector2* position2;
} line;

/**
 * Creates a new line with the given coordinates.
 */
line* new_line(float x0, float y0, float x1, float y1);

/**
 * Frees the line 'ln.
 */
void free_line(line* ln);
#endif
