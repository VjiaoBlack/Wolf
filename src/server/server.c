#include "server.h"

void read_from_player_thread(int id) {
    read(serv_ips[id], &player_inputs[id], 1);
    player_inputs_updated[id] = 1;
}

void write_to_players_from(int id) {
    int i;
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (i != id) {
            write(serv_ips[i],player_inputs,MAX_PLAYERS+1);
        }
    }
}

int main(int argc, char *argv[]) {

    int listenfd = 0;
    struct sockaddr_in serv_addr;
    num_players = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // maximum 4 connections
    listen(listenfd, MAX_PLAYERS);

    while(1) {
        serv_ips[num_players] = accept(listenfd, (struct sockaddr*)NULL, NULL);
        num_players++;

        printf("Got a connection from %s on port %d\n", inet_ntoa(serv_addr.sin_addr), htons(serv_addr.sin_port));

        if (pthread_create(&threads[num_players-1], NULL, &handle, &serv_ips[num_players-1]) != 0) {
            fprintf(stderr, "Failed to create thread\n");
        }

        // continue looping asap
    }
}

int is_updated() {
    int i;
    int sum = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        sum += player_inputs_updated[i];
    }
    return sum == num_players;
}

void *handle(void *pnewsock) {
    // int connfd = * (int*)pnewsock;

    int i;
    // assign player ID to thread
    int player_id = num_players - 1;

    // notify client of ID

    while (1) {
        // get input from client
        read_from_player_thread(player_id);

        while (!is_updated());

        // write to other players
        write_to_players_from(player_id);

        // set player_input to old if it's not -1
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (player_inputs_updated[i]) {
                player_inputs_updated[i] = 0;
            }
        }
    }

}
