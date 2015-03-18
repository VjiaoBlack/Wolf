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

/*
 *	initalizes all of the walls of the mesh as a collection of points (obstacles)
 */
void initialize_terrain(mesh *m);

/*
 *  checks whether location loc is near an obstacle
 */
int is_open(vector2 *loc);

/*
 *  frees up memory space from terrain
 */
void free_terrain();

terrain *ter;

#endif