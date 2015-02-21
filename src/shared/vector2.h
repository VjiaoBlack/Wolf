#ifndef VECTOR2_H
#define VECTOR2_H

/**
 * @file        vecto2.h
 * @author      John Lekberg
 * @date        2015-02-11
 * @modified    2015-02-11
 * @copyright   MIT License
 *
 * Holds a two dimensional vector.
 */

typedef struct vector2 {
    float x, y;
} vector2;

vector2 *new_vector2(float x, float y);
void    free_vector2(vector2 *vec);
#endif
