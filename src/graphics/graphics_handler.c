#include "graphics_handler.h"


void draw_line(line* lin) {



    SDL_RenderDrawLine(renderer, (int) lin->position1->x, (int) lin->position1->y, (int) lin->position2->x, (int) lin->position2->y);





}
