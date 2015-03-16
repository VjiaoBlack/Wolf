#include "server.h"

void read_from_player_thread(int id) {

    // printf("---> %d\n", id);
    if (0 >= read(serv_ips[id], player_inputs + sizeof(char) * id * 3, 3)) {

        exit_thread(id);
    }
    // printf("read from %d.\n", id);
    player_inputs_updated[id] = 1;
}

void write_to_player(int id) {
    // int i;
    // for (i = 0; i < MAX_PLAYERS; i++) {
        // if (i != id && serv_ips[i] > -1) {
            write(serv_ips[id],player_inputs,12);
        // }
    // }
}

int main(int argc, char *argv[]) {

    int listenfd = 0;
    struct sockaddr_in serv_addr;
    int sock;


    num_players = 0;
    next_empty = 0;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // setup variables, - means no player, 0 means no input
    memset(player_inputs, '-', sizeof(char) * 12);
    memset(player_inputs_updated, -1, sizeof(int) * 4);
    memset(player_states, -1, sizeof(int) * 4);
    memset(serv_ips, -1, sizeof(int) * 4);
    memset(connected, 0, sizeof(int) * 4);

    player_inputs[12] = '\0';




    // maximum 4 connections
    listen(listenfd, MAX_PLAYERS);
    while(1) {

        // WARNING - NEXT LINE DOES NOT HANDLE PLAYER QUIT AND THEN JOIN
        sock = accept(listenfd, (struct sockaddr*)NULL, NULL);

        int i;
        next_empty = -1;
        for (i = 0; i < 4; i++) {
            if (next_empty == -1 && !connected[i]) {
                next_empty = i;
                printf("  %d is the first unconnected player. Players now: %d\n", i, ++num_players);
                break;
            }
        }

        serv_ips[next_empty] = sock;
        connected[next_empty] = 1;



        printf("  Got a connection from %s on port %d\n", inet_ntoa(serv_addr.sin_addr), htons(serv_addr.sin_port));

        if (pthread_create(&threads[next_empty], NULL, &handle, &serv_ips[next_empty]) != 0) {
            fprintf(stderr, "Failed to create thread\n");
        }

        // continue looping asap
    }
}

int is_updated(int id) { // is kinda broken.
    int i;
    int sum = 0;
    for (i = 0; i < MAX_PLAYERS; i++) {
        if (player_inputs_updated[i] > -1) {
            sum += player_inputs_updated[i];
        }
    }
    printf("%d: |%d %d|\n", id, sum, num_players);
    return sum == num_players;
}

void *handle(void *pnewsock) {
    char id_buf[4];

    // int connfd = * (int*)pnewsock;


    int i;


    int ready_to_read;
    int ready_to_write;

    // assign player ID to thread
    int player_id = next_empty;

    // send player_id info
    sprintf(id_buf, "%d", next_empty);
    write(serv_ips[next_empty], id_buf, strlen(id_buf) + 1);
    printf("  sent player id: %s\n", id_buf);

    // try to have the is_updated function testing in the CENTRAL main function...
    while (1) {
        // update
        // check_players();


        // clear input for unconnected players
        for (i = 0; i<4; i++) {
            if (!connected[i]) {
                memset(player_inputs + 3 * i, '-', sizeof(char) * 3);
            }
        }

        // get input from client
        player_states[player_id] = READING;

        ready_to_read = 0;
        // printf("%d ready to read\n", player_id);
        while (!ready_to_read) {
            // printf("%d waiting to read\n", player_id);
            for (int i = 0; i < 4; i++) {
                if (connected[i]) {
                    if (player_states[i] != READING) {
                        ready_to_read = -1;
                        // printf("%d sees %d not ready to read\n", player_id, i);
                        break;
                    }
                }
            }
            if (ready_to_read == 0) {
                ready_to_read = 1;
            } else if (ready_to_read == -1) {
                ready_to_read = 0;
            }
            usleep(10);
        }
        memset(player_inputs, '-', sizeof(char) * 12);

        read_from_player_thread(player_id);
        // printf("%d read\n", player_id);


        // write to other players
        player_states[player_id] = WRITING;

        ready_to_write = 0;
        // printf("%d ready to write\n", player_id);
        while (!ready_to_write) {
            // printf("%d waiting to write\n", player_id);
            for (int i = 0; i < 4; i++) {
                if (connected[i]) {
                    if (player_states[i] != WRITING) {
                        ready_to_write = -1;
                        // printf("%d sees %d not ready to write\n", player_id, i);
                        break;
                    }
                }
            }
            if (ready_to_write == 0) {
                ready_to_write = 1;
            } else if (ready_to_write == -1) {
                ready_to_write = 0;
            }
            usleep(10);
        }
        write_to_player(player_id);
        // printf("%d wrote\n", player_id);

        // set player_input to old if it's not -1
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (player_inputs_updated[i]) {
                player_inputs_updated[i] = 0;
            }
        }

        // printf("%d end\n\n", player_id);
    }

}

// updates num players, checks to see which player positions are null, etc...
void check_players() {

    int i;
    for (i = 0; i < 4; i++) {
        // this code for disconnected checking doesnt work.
        if (player_inputs[i*3] == 'q') {
            exit_thread(i);
        }
    }
}


void exit_thread(int id) {
    num_players--;
    next_empty = id;
    connected[id] = 0;
    player_inputs_updated[id] = -1;
    player_states[id] = -1;
    printf("  %d has disconnected.\n", id);

    pthread_exit(threads[id]);
}
