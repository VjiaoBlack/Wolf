#ifndef GRAPHICS_HANDLER_H
#define GRAPHICS_HANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../shared/line.h"
#include "../shared/entity.h"
#include "../shared/world.h"



SDL_Window* window;
SDL_Texture* texture;
SDL_Renderer* renderer;

extern world* game_world;

void draw_line(line* lin);
void draw_entity(entity* ent);

void init_sdl();

#endif
