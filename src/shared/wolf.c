// Victor 2/20

#include "wolf.h"

int main(int argc, char** argv) {




    int delay;
    struct timeval pre, post;


    if (argc > 1) {
        init_multiplayer(strdup(argv[1]));
    } else {
        init_multiplayer("");
        player_id = -1;
        printf("Running in single-player mode!\n");
    }

    init_general();
    init_sdl();



    while(1) {
        gettimeofday(&pre, NULL);

        get_input();

        if (keys_held[SDLK_q]) {
            write(server_ip, "qqq", 4);
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

    free_mesh(game_mesh);


    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);

}

int isready(int fd) {
    int rc;
    fd_set fds;
    struct timeval tv;

    FD_ZERO(&fds);
    FD_SET(fd,&fds);

    tv.tv_sec = tv.tv_usec = 0;
    rc = select(fd+1, &fds, NULL, NULL, &tv);
    if (rc < 0)
      return -1;

    return FD_ISSET(fd,&fds) ? 1 : 0;
}

void init_general() {

    mspf = 1000 / FPS;

    output_buf[3] = '\0';

    mouse_x = mouse_y = 0;
    mouse_xvel = mouse_yvel = 0;

    FILE* map = fopen("res/testmap.map", "r");

    if (map == NULL) {
        printf("Invalid map file: check tools/map_visualizer/testmap.map\n");
    } else {
        printf("loaded map\n");
    }

    game_mesh = mesh_load_from_file(map);




}

void update() {
    update_input();
}


void update_input() {

    if (keys_held['w']) {
        output_buf[ID_MOVEMENT] = 'w';
    } else if (keys_held['s']) {
        output_buf[ID_MOVEMENT] = 's';
    } else if (keys_held['c']) {
        output_buf[ID_MOVEMENT] = 'c';
    } else if (keys_held['z']) {
        output_buf[ID_MOVEMENT] = 'z';
    } else {
        output_buf[ID_MOVEMENT] = '0';
    }


    if (keys_held['a']) {
        output_buf[ID_TURNING] = 'a';
    } else if (keys_held['d']) {
        output_buf[ID_TURNING] = 'd';
    } else {
        output_buf[ID_TURNING] = '0';
    }

    if (keys_held[' ']) {
        output_buf[ID_SHOOTING] = ' ';
    } else {
        output_buf[ID_SHOOTING] = '0';
    }

    if (server_ip > -1) {
        write(server_ip, output_buf, 3);

        read(server_ip, input_buf, 512);

        // printf("%s--\n", input_buf);

        // update the  other players.
    }

}

void draw() {
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);


    void (*draw_line_p)(line*);
    draw_line_p = &draw_line;

    mesh_for_each_line(game_mesh,draw_line_p);

    int kind, id, mult_id, hp, x, y, dir;

    int i = 0; // offset.
    while (i < 511 && input_buf[i] != '\0') {
        // until the end of input_buf:

        // scan
        sscanf(input_buf + i,"%d,%d,%d:%d,%d,%d,%d\n", &kind, &id, &mult_id, &hp, &x, &y, &dir); // 0 is npc, 1 is player

                // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.

        SDL_Rect r;
        r.x = x - 10;
        r.y = y - 10;
        r.w = 20;
        r.h = 20;


        switch (kind) {
            case 0:
                // NPC
                SDL_SetRenderDrawColor( renderer, (int) (1.55 * (float) hp) + 100, 100, 100, 255 );
                SDL_RenderFillRect( renderer, &r );
                SDL_RenderDrawLine(renderer,x,y,x + 20*cos((float) dir / 10.0),y + 20*sin((float) dir / 10.0));


                break;
            case 1:
                // PLAYER
                switch(mult_id) {
                    case 0:
                        SDL_SetRenderDrawColor( renderer, 100, 100, (int) (1.55 * (float) hp) + 100, 255 );
                        break;
                    case 1:
                        SDL_SetRenderDrawColor( renderer, 100, (int) (1.55 * (float) hp) + 100, 100, 255 );
                        break;
                    case 2:
                        SDL_SetRenderDrawColor( renderer, 100, (int) (2.00 * (float) hp) + 100, (int) (2.00 * (float) hp) + 100, 255 );
                        break;
                    case 3:
                        SDL_SetRenderDrawColor( renderer, (int) (2.00 * (float) hp) + 100, 100, (int) (2.00 * (float) hp) + 100, 255 );
                        break;

                }
                SDL_RenderFillRect( renderer, &r );
                SDL_RenderDrawLine(renderer,x,y,x + 20*cos((float) dir / 10.0),y + 20*sin((float) dir / 10.0));

                break;
            case 2:
                // BULLET
                SDL_RenderDrawLine(renderer,x-10*cos((float) dir / 10.0),y-10*sin((float) dir / 10.0),x ,y);

                break;
        }



        // Render rect


        // inc i
        while (input_buf[i] != '\n') {
            ++i;
        }
        ++i;

    }

    // void (*draw_entity_p)(entity*);
    // draw_entity_p = &draw_entity;
    // for_each_entity(game_mesh->w_store,draw_entity_p);

    SDL_RenderPresent(renderer);


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void init_multiplayer(char* serv) {
    if (strlen(serv) == 0) {
        server_ip = -1;
        printf("no server\n");
        return;
    }

    if ((server_ip = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Error : Could not create socket \n");
        exit(1);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if (inet_pton(AF_INET, serv, &serv_addr.sin_addr)<=0) {
        printf("\n inet_pton error occured\n");
        exit(1);
    }

    if (connect(server_ip, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\n Error : Connect Failed \n");
        exit(1);

    }

    char id_buf[4];

    // get player_id
    printf("reading player id...\n");
    read(server_ip, id_buf, 5);
    player_id = atoi(id_buf);
    printf("read player id! %d\n", player_id);

    memset(input_buf, '\0', 512);
}
