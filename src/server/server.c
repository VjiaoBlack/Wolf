#include "server.h"

void read_from_player_thread(int id) {
    // printf("pre-read\n");

    // wait until something is read

    if (0 >= read(client_ips[id], input_buf + sizeof(char) * id * 3, 3)) {
        memset(input_buf+sizeof(char) * id * 3, '-', 3);
    } else {
        yes = 1;
    }
    // printf("post-read\n");
}

void write_to_player(int id) {
    // printf("pre-write\n");
    serialize_world(output_buf, game_world);
    printf("%s\n", output_buf);
    write(client_ips[id],output_buf, 512 * sizeof(char));
}

int main(int argc, char *argv[]) {

    int sock;
    yes = 0;


    num_players = 0;
    next_empty = 0;

    int listenfd = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // using nonblocking sockets
    fcntl(listenfd, F_SETFL, O_NONBLOCK);

    init_general();


    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // setup variables, - means no player, 0 means no input
    memset(client_ips, -1, sizeof(int) * 4);
    memset(connected, 0, sizeof(int) * 4);

    input_buf[12] = '\0';

    char id_buf[4];



    // maximum 4 connections
    // use non-blocking sockets.
    listen(listenfd, MAX_PLAYERS);
    while(1) {
        if ((sock = accept(listenfd, (struct sockaddr*)NULL, NULL)) != -1) {
            printf("  Got a connection from %s on port %d\n", inet_ntoa(serv_addr.sin_addr), htons(serv_addr.sin_port));

            int i;
            next_empty = -1;
            for (i = 0; i < 4; i++) {
                if (next_empty == -1 && !connected[i]) {
                    next_empty = i;
                    printf("  %d is the first unconnected player. Players now: %d\n", i, ++num_players);
                    break;
                }
            }

            client_ips[next_empty] = sock;
            connected[next_empty] = 1;

            // send player_id info
            sprintf(id_buf, "%d", next_empty);
            write(client_ips[next_empty], id_buf, strlen(id_buf) + 1);


            // finish setting up player: create player etc
            // NEW PLAYER
            m_player_pos[next_empty] = new_vector2(300,300);
            m_player_angle[next_empty] = (float*) malloc(sizeof(float));
            *m_player_angle[next_empty] = 0;
            player_pointers[next_empty] = add_new_entity(100,game_world,Player,m_player_pos[next_empty],m_player_angle[next_empty], next_empty);
        }

        handle();



    }
}

void handle() {

    int i;

    while (!yes && num_players) {
        printf("%d %d\n", yes, num_players);
    for (i = 0; i < 4; i++) {
        if (connected[i]) {
            read_from_player_thread(i);
        } else {
            memset(input_buf+sizeof(char) * i * 3, '-', 3);
        }
    }
    }
    if (yes) {
        update();
    }
    for (i = 0; i < 4; i++) {
        if (connected[i]) {
            write_to_player(i);
        }
    }
    yes = 0;

    usleep(1000000/28); // worst fix ever.
    // what should happen is - coordinated read/writes,
    // or clearing the read buffer.
}

// updates num players, checks to see which player positions are null, etc...
void check_players() {

    int i;
    for (i = 0; i < 4; i++) {
        // this code for disconnected checking doesnt work.
        if (input_buf[i*3] == 'q') {
            printf("quit\n");
            exit_player(i);
        }
    }
}


void exit_player(int id) {
    num_players--;
    next_empty = id;
    connected[id] = 0;
    // EXIT PLAYER
    printf("what\n");
    free_entity(player_pointers[id], game_world->w_store);
    printf("  %d has disconnected.\n", id);
}

void init_general() {


    mouse_x = mouse_y = 0;
    mouse_xvel = mouse_yvel = 0;

    game_world = new_world();

    next_empty = 0;

    // this creates a new enemy
    float* enemypos = (float*) malloc(sizeof(float));
    *enemypos = 0;
    add_new_entity(100,game_world,NPC,new_vector2(100,100),enemypos, -1);
}

void update() {
    update_input();
    void (*update_enemy_p)(entity*);
    update_enemy_p = &update_enemy;
    for_each_entity(game_world->w_store,update_enemy_p);
}


void update_input() {
    int i;
    float si;
    float co;
    // iterate through all players to do following:
    for (i = 0; i < 4; i++) {
        // only update connected players
        if (!connected[i])
            continue;

        si = sin(*m_player_angle[i]);
        co = cos(*m_player_angle[i]);

        float x = 0;
        float y = 0;

        // analyze inputs
        if (input_buf[i*3]=='w') {
            y = 2 * si;
            x = 2 * co;
        } else if (input_buf[i*3]=='s') {
            y = -2 * si;
            x = -2 * co;
        } else if (input_buf[i*3]=='c') {
            y = 2 * co;
            x = -2 * si;
        } else if (input_buf[i*3]=='z') {
            y = -2 * co;
            x = 2 * si;
        }


        // if (valid_move(m_player_pos[i], x, y, game_world)) {
            m_player_pos[i]->x += x;
            m_player_pos[i]->y += y;
        // }

        if (input_buf[i*3+1]=='a') {
            *m_player_angle[i]-=.1;
        } else if (input_buf[i*3+1]=='d') {
            *m_player_angle[i]+=.1;
        }


        if (input_buf[i*3+2]==' ') {
            // THERE IS A SHOT
            // DRAW THE LINE
            //
        }
    }

}

void serialize_world(char* str, world* worl) {
    memset(str,'\0',512);

    char ser_buf[64];

    int i = 0;
    int c = 0;
    while (c < worl->w_store->num_entities) {

        if (worl->w_store->entities[i]) {
            memset(ser_buf,'\0',64);

            // for each non-null entity;

            entity* ent = worl->w_store->entities[i];

            sprintf(ser_buf,"%d,%d,%d:%d,%d,%d,%d\n", ent->kind == Player, ent->ID, ent->multi_id, ent->health, (int)ent->position->x, (int)ent->position->y, (int)(*ent->bearing * 10));


            strcat(output_buf,ser_buf);

            c++;
        }
        i++;
    }




}



















