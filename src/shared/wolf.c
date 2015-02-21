// Victor 2/20

#include "wolf.h"

int main(int argc, char** argv) {


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    mspf = 1000 / FPS;

    int delay;



    mouse_x = mouse_y = 0;
    mouse_xvel = mouse_yvel = 0;

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


    game_world = new_world();

    init_input();

    printf("-~Wolf~-\n");

    struct timeval pre, post;


    while(1) {
        gettimeofday(&pre, NULL);

        get_input();
        if (keys_held[SDLK_q]) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }

        draw();




        gettimeofday(&post, NULL);


        if ( (delay = (post.tv_usec - pre.tv_usec) / 1000 + (post.tv_sec - pre.tv_sec)* 1000) < mspf) {
            SDL_Delay(mspf - delay);
        }

    }

    free_world(game_world);

    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);

}

void draw() {
    SDL_RenderClear(renderer);


    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );


    void (*draw_line_p)(line*);
    draw_line_p = &draw_line;
    mesh_for_each_line(game_world->w_mesh,draw_line_p);


    // Render rect
    SDL_RenderFillRect( renderer, &r );


    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
