#ifndef PHYSICS_INFO_H
#define PHYSICS_INFO_H

#include "../shared/vector2.h"
#include "../shared/mesh.h"
#include "../shared/line.h"

#include <math.h>

#define RADIUS 2
#define CIRCLES_PER_RADIUS 2

typedef struct terrain {
	vector2 **obstacles;
	int num_obstacles;
} terrain; 

void initialize_terrain(mesh *m);

int is_open(vector2 *loc);

void free_terrain();

terrain *ter;

#endif