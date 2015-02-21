// Victor 2/20

#include "wolf.h"

int main(int argc, char** argv) {
    int delay;
    struct timeval pre, post;

    init_general();
    init_sdl();
    init_input();

    while(1) {
        gettimeofday(&pre, NULL);

        get_input();

        if (keys_held[SDLK_q]) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }

        update();
        draw();

        gettimeofday(&post, NULL);
        if ( (delay = (post.tv_usec - pre.tv_usec) / 1000 + (post.tv_sec - pre.tv_sec)* 1000) < mspf) {
            SDL_Delay(mspf - delay);
        }
    }

    free_world(game_world);

    free_vector2(player_pos);

    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);

}

void init_general() {
    mspf = 1000 / FPS;

    mouse_x = mouse_y = 0;
    mouse_xvel = mouse_yvel = 0;

    game_world = new_world();

    player_pos = new_vector2(100,100);
}

void draw() {
    SDL_RenderClear(renderer);

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect r;
    r.x = player_pos->x - 10;
    r.y = player_pos->y - 10;
    r.w = 20;
    r.h = 20;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 100, 100, 255, 255 );


    void (*draw_line_p)(line*);
    draw_line_p = &draw_line;
    mesh_for_each_line(game_world->w_mesh,draw_line_p);


    // Render rect
    SDL_RenderFillRect( renderer, &r );

    SDL_RenderPresent(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void update() {
    float si = sin(player_angle);
    float co = cos(player_angle);


    if (keys_held['w']) {
        player_pos->y += 2 * si;
        player_pos->x += 2 * co;
    }
    if (keys_held['s']) {
        player_pos->y -= 2 * si;
        player_pos->x -= 2 * co;
    }
    if (keys_held['c']) {
        player_pos->y += 2 * co;
        player_pos->x -= 2 * si;
    }
    if (keys_held['z']) {
        player_pos->y -= 2 * co;
        player_pos->x += 2 * si;
    }

    if (keys_held['a']) {
        player_angle-=.1;
    }
    if (keys_held['d']) {
        player_angle+=.1;
    }

}
