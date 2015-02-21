#include "vector2.h"

vector2 *new_vector2(float x, float y) {
    vector2 *result = (vector2 *)malloc(sizeof(vector2));
    result->x = x;
    result->y = y;
    return result;
}

void free_vector2(vector2 *vec) {
    free((void*)vec);
}

vector2 *add(vector2 *a, vector2 *b) {
    vector2* c = (vector2*) malloc(sizeof(vector2));

    c->x = a->x + b->x;
    c->y = a->y + b->y;

    return c;
}

float distance(vector2 *a, vector2 *b) {
    return sqrt( pow(a->x - b->x, 2) + pow(a->y - b->y, 2) );
}

float angle(vector2 *source, vector2 *target) {
    // returns angle from source to target.

    double src_angle = atan2(source->y, source->x);
    double tar_angle = atan2(target->y, target->x);

    return (float) (tar_angle - src_angle);
}
