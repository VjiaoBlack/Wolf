#ifndef PHYSICS_HANDLER_H
#define PHYSICS_HANDLER_H

#include "../physics/physics_info.h"
#include "../shared/vector2.h"
#include "../shared/world.h"
#include "../shared/mesh.h"
#include "../shared/line.h"

#include <unistd.h>

/*
 *  checks whether a move is valid
 */
int valid_move(vector2 *pos, int x_off, int y_off, world *w);

#endif