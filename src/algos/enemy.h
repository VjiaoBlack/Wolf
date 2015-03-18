#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include "../shared/world.h"
#include "../server/server.h"
#include "../physics/physics_handler.h"
#include <math.h>


extern world* game_world;
extern vector2* player_pos;
extern float* player_angle;
// gets the world info directly from gameworld
void update_enemy(entity* ent);
void update_bullet(entity*ent);


#endif
