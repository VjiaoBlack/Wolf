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

#define MAX_PLAYERS 4

#define ID_MOVEMENT 0
#define ID_TURNING  1
#define ID_SHOOTING 2

uint32_t serv_ips[4];
int connected[4]; // says whether the player spot is connected or not
char player_inputs[13];
int player_inputs_updated[4]; // -1 for n/a, 0 for old, 1 for new.
pthread_t threads[4];
int num_players;

int main(int, char**);
void* handle(void*);

void read_from_player_thread(int);
void write_to_players_from(int);
int is_updated();

#endif
