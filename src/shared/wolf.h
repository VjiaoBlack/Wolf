#ifndef WOLF_H

#define WOLF_H
#define FPS 60

int mspf;

#define ID_MOVEMENT 0
#define ID_TURNING  1
#define ID_SHOOTING 2

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <sys/time.h>
#include <math.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include "../input/input_handler.h"
#include "../graphics/graphics_handler.h"
#include "../shared/world.h"
#include "../shared/line.h"


int player_id;

struct sockaddr_in serv_addr;
int server_ip;
char output_buf[4];
char input_buf[512];

mesh* game_mesh;




int main(int argc, char** argv);
void draw();
void init_general();
void update();
void update_input();
void init_multiplayer(char* serv_str);

#endif
