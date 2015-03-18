// Victor 2/20

#include "wolf.h"

int main(int argc, char** argv) {
    int delay;
    struct timeval pre, post;

    init_general();
    init_sdl();
    if (argc > 1) {
        init_multiplayer(strdup(argv[1]));
    } else {
        init_multiplayer("");
        player_id = -1;
        printf("Running in single-player mode!\n");
    }

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

    free_world(game_world);

    free_vector2(player_pos);

    free_terrain(); 

    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);

}

void init_general() {
    server_msg[3] = '\0';

    mspf = 1000 / FPS;

    mouse_x = mouse_y = 0;
    mouse_xvel = mouse_yvel = 0;

    game_world = new_world();
    initialize_terrain(game_world->w_mesh);

    player_pos = new_vector2(300,300);
    player_angle = (float*) malloc(sizeof(float));
    *player_angle = 0;

    add_new_entity(100,game_world,Player,player_pos,player_angle, player_id);


    // this creates a new enemy
    float* enemypos = (float*) malloc(sizeof(float));
    *enemypos = 0;
    add_new_entity(100,game_world,NPC,new_vector2(25,25),enemypos, -1);
}
void update() {
    update_input();
    void (*update_enemy_p)(entity*);
    update_enemy_p = &update_enemy;
    for_each_entity(game_world->w_store,update_enemy_p);
}


void update_input() {


    float si = sin(*player_angle);
    float co = cos(*player_angle);


    if (keys_held['w']) {
        player_pos->y += 2 * si;
        player_pos->x += 2 * co;
        server_msg[ID_MOVEMENT] = 'w';
    } else if (keys_held['s']) {
        player_pos->y -= 2 * si;
        player_pos->x -= 2 * co;
        server_msg[ID_MOVEMENT] = 's';
    } else if (keys_held['c']) {
        player_pos->y += 2 * co;
        player_pos->x -= 2 * si;
        server_msg[ID_MOVEMENT] = 'c';
    } else if (keys_held['z']) {
        player_pos->y -= 2 * co;
        player_pos->x += 2 * si;
        server_msg[ID_MOVEMENT] = 'z';
    } else {
        server_msg[ID_MOVEMENT] = '0';
    }


    if (keys_held['a']) {
        *player_angle-=.1;
        server_msg[ID_TURNING] = 'a';
    } else if (keys_held['d']) {
        *player_angle+=.1;
        server_msg[ID_TURNING] = 'd';
    } else {
        server_msg[ID_TURNING] = '0';
    }

    server_msg[ID_SHOOTING] = '0';

    if (server_ip > -1) {
        write(server_ip, server_msg, 3);
        printf("%d: %s\n", player_id, server_msg);
    }

}

void draw() {
    SDL_RenderClear(renderer);

    void (*draw_line_p)(line*);
    draw_line_p = &draw_line;
    mesh_for_each_line(game_world->w_mesh,draw_line_p);

    void (*draw_entity_p)(entity*);
    draw_entity_p = &draw_entity;
    for_each_entity(game_world->w_store,draw_entity_p);

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
    printf("read player id!\n");

}
