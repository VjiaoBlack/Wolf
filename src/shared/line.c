#include "line.h"

line* new_line(float x0, float y0, float x1, float y1) {
    line* result = (line*)malloc(sizeof(line));
    result->position1 = new_vector2(x0, y0);
    result->position2 = new_vector2(x1, y1);
    return result;
}

void free_line(line *ln) {
    free_vector2(ln->position1);
    free_vector2(ln->position2);
    free((void*)ln);
}
