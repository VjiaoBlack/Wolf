#ifndef VECTOR2_H
#define VECTOR2_H

/**
 * @file        mesh.h
 * @author      John Lekberg
 * @date        2015-02-11
 * @modified    2015-02-11
 * @copyright   MIT License
 *
 * The mesh holds the static part of a level.
 */


typedef struct vector2 {
    double x, y;
} vector2;

vector2 *new_vector2(double x, double y);
void    free_vector2(vector2 vec);
#endif
