#include "mesh.c"

typedef struct line {
	vector *a;
	vector *b;
} line;

typedef struct mesh {
	line **lines;
} mesh;
