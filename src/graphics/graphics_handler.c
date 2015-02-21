#include "graphics_handler.h"


void draw_line(line* lin) {
    SDL_RenderDrawLine(renderer, (int) lin->position1->x, (int) lin->position1->y, (int) lin->position2->x, (int) lin->position2->y);
}

void draw_entity(entity* ent) {

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = ent->position->x - 10;
    r.y = ent->position->y - 10;
    r.w = 20;
    r.h = 20;

    // Set render color to blue ( rect will be rendered in this color )
    if (ent->kind == Player)
        SDL_SetRenderDrawColor( renderer, 100, 100, 255, 255 );
    else
        SDL_SetRenderDrawColor( renderer, 255, 100, 100, 255 );

    void (*draw_line_p)(line*);
    draw_line_p = &draw_line;
    mesh_for_each_line(game_world->w_mesh,draw_line_p);

    SDL_RenderDrawLine(renderer, (int) ent->position->x,
                                (int) ent->position->y,
                                (int) ent->position->x + 20*cos(*ent->bearing),
                                (int) ent->position->y + 20*sin(*ent->bearing));

    // Render rect
    SDL_RenderFillRect( renderer, &r );

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
