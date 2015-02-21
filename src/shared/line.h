#ifndef LINE_H
#define LINE_H

#include "vector2.h"

typedef struct line {
    vector2 position1, position2;
} line;

/**
 * Creates a new line with the given coordinates.
 */
line* new_line(double x0, double y0, double x1, double y1);

/**
 * Frees the line 'ln.
 */
void free_line(line* ln);
#endif
