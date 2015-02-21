#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

typedef struct vector {
	int x;
	int y;
} vector;

vector *add(vector *a, vector *b);

float distance(vector *a, vector *b);

float angle(vector *source, vector *target);