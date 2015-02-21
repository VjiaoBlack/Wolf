#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int keys_held[323];
int sdl_quit;

SDL_Window* window;
SDL_Texture* texture;
SDL_Renderer* renderer;

int mouse_x, mouse_y;
int mouse_xvel, mouse_yvel;

void init_input();
void get_input();

#endif
