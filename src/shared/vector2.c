#include "vector2.h"

vector2 *new_vector(double x, double y) {
    vector2 *result = (vector2 *)malloc(sizeof(vector2));
    result->x = x;
    result->y = y;
    return result;
}

void free_vector2(vector2 *vec) {
    free((void*)vec);
}
