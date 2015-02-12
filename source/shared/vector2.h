#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct _vector2 {
    double x, y;
} _vector2, *vector2;

vector2 new_vector2(double x, double y);
void    free_vector2(vector2 vec);
#endif
