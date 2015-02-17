#include "line.h"

line* new_line(double x0, double y0, double x1, double y1) {
    line* result = (line*)malloc(sizeof(line));
    line->position1 = new_vector(x0, y0);
    line->position2 = new_vector(x1, y1);
    return result;
}

void free_line(line *ln) {
    free_vector2(ln->position1);
    free_vector2(ln->position2);
    free((void*)ln);
}
