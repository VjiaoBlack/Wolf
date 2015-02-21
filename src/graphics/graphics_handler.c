#include "graphics_handler.h"


void draw_line(line* lin) {
    SDL_RenderDrawLine(renderer, (int) lin->position1->x, (int) lin->position1->y, (int) lin->position2->x, (int) lin->position2->y);
}


void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          800, 640,
                           SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Couldn't set window mode %d x %d: %s\n", 800, 640, SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer( window, 0, SDL_RENDERER_ACCELERATED);
}
