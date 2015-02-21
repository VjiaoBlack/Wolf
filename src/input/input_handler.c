// Victor 2/20

#include "input_handler.h"

void init_input() {
    memset(keys_held,0,sizeof(keys_held));
    sdl_quit = 0;
}

// gets input from the user
void get_input() {
    printf("called\n");
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            sdl_quit = 1;
        }
        if (event.type == SDL_KEYUP) {  // any key is released
            keys_held[event.key.keysym.sym] = 0;
        }
        if (event.type == SDL_KEYDOWN) {  // any key is pressed
            keys_held[event.key.keysym.sym] = 1;
        }
        if (event.type == SDL_MOUSEMOTION) {
            mouse_x = event.motion.x;
            mouse_y = event.motion.y;

            mouse_xvel = event.motion.xrel;
            mouse_yvel = event.motion.yrel;
        }
    }
}
