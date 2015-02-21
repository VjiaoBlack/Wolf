#include <stdlib.h>
#include <stdio.h>

typedef struct vector vector;

vector *add(vector *a, vector *b);

float distance(vector *a, vector *b);

float angle(vector *source, vector *target);