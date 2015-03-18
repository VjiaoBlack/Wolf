#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <stdint.h>

#include <fcntl.h>

#define MAX_PLAYERS 4

#define ID_MOVEMENT 0
#define ID_TURNING  1
#define ID_SHOOTING 2

#define READING 0
#define WRITING 1

uint32_t client_ips[4];
int connected[4]; // says whether the player spot is connected or not
char input_buf[13];
char output_buf[512];

int num_players;
int next_empty;

// int lol;

int main(int, char**);
void handle();

void read_from_player_thread(int);
void write_to_player(int);
int is_updated(int);

void check_players();


void exit_player(int);




// #define PLAYER_VEL

#define ID_MOVEMENT 0
#define ID_TURNING  1
#define ID_SHOOTING 2

// #include <stdio.h>
// #include <stdlib.h>
// #include <SDL2/SDL.h>
// #include <sys/time.h>
// #include <math.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <netinet/in.h>
// #include <netdb.h>
// #include <unistd.h>
// #include <errno.h>
// #include <arpa/inet.h>

#include "../input/input_handler.h"
#include "../graphics/graphics_handler.h"
#include "../shared/world.h"
#include "../algos/enemy.h"

int yes;


entity* player_pointers[4];

world* game_world;

vector2* m_player_pos[4];
float* m_player_angle[4];

void init_general();
void update();
void update_input();


void serialize_world(char*, world*);

#endif

