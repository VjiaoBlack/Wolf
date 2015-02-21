#ifndef WOLF_H

#define WOLF_H


#define FPS 60

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <sys/time.h>
#include <math.h>
#include "../input/input_handler.h"
#include "mesh.h"
#include "world.h"
#include "../graphics/graphics_handler.h"

int mspf;
world* game_world;

vector2* player_pos;
float player_angle;

int main(int argc, char** argv);
void draw();
void init_general();
void update();

#endif
