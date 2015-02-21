#include "world.h"

typedef struct world {
	vector size_vector

	actor **actors; 

	mesh *mesh;
} world;