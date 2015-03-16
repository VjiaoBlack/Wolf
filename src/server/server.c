#include "server.h"

void read_from_player_thread(int id) {

    printf("---> %d\n", id);
    if (0 >= read(serv_ips[id], player_inputs + sizeof(char) * id * 3, 3)) {
        printf("QUIT\n");
        exit(1);
    }
    printf("read from %d.\n", id);
    // printf("%d: |%c,%c,%c| \n",   id, player_inputs[id*3], player_inputs[id*3+1], player_inputs[id*3+2]);
    player_inputs_updated[id] = 1;
}

void write_to_players_from(int id) {
    // int i;
    // for (i = 0; i < MAX_PLAYERS; i++) {
    //     if (i != id && serv_ips[i] > -1) {
    //         write(serv_ips[i],player_inputs,13);
    //     }
    // }
}

int main(int argc, char *argv[]) {

    // lol = 0;
    is_okay = 0;
    done = 0;
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
    memset(serv_ips, -1, sizeof(int) * 4);
    memset(connected, 0, sizeof(int) * 4);

    player_inputs[12] = '\0';




    // maximum 4 connections
    listen(listenfd, MAX_PLAYERS);
    while(1) {

        // WARNING - NEXT LINE DOES NOT HANDLE PLAYER QUIT AND THEN JOIN
        sock = accept(listenfd, (struct sockaddr*)NULL, NULL);

        // update
        check_players();
        okaypass = 0;

        bypass = 1;

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

    // assign player ID to thread
    int player_id = next_empty;

    // send player_id info
    sprintf(id_buf, "%d", next_empty);
    write(serv_ips[next_empty], id_buf, strlen(id_buf) + 1);
    printf("  sent player id: %s\n", id_buf);

    // try to have the is_updated function testing in the CENTRAL main function...
    while (1) {
        // clear player input
        memset(player_inputs, '-', sizeof(char) * 12);

        while ((done != 0)) {
            if (bypass) {
                break;
            }
            printf("%d: things not completed... byp: %d\n", player_id, bypass);
            sleep(1);
        }
        done = num_players;


        // get input from client
        // printf("%d -- %d\n", player_id, ++lol);
        // while ( lol < num_players ) {
        //     printf("%d..lol.\n", player_id);
        //     sleep(1);
        // }

        read_from_player_thread(player_id);
        is_okay++;
        while (is_okay != num_players) {
            if (okaypass)  {
                okaypass = 0;
                break;
            }
            printf("%d: not okay... %d, %d\n", player_id, is_okay, num_players);
            sleep(1);
        }
        printf("%d: achieved okay... %d, %d\n", player_id, is_okay, num_players);


        while (!is_updated(player_id)) {
            sleep(1);
        }


        is_okay--;
        okaypass = 1;
        while (is_okay > 0) {
            printf("%d: is watiing, %d\n", player_id, is_okay);
            sleep(1);
        }
        printf("%d: is ookay! %d\n", player_id, is_okay);
        // printf("%d: |%c%c%c| \n", player_id, player_inputs[player_id], player_inputs[player_id], player_inputs[player_id]);
        // write to other players
        // write_to_players_from(player_id);

        // set player_input to old if it's not -1
        for (i = 0; i < MAX_PLAYERS; i++) {
            if (player_inputs_updated[i]) {
                player_inputs_updated[i] = 0;
            }
        }

        // lol = 0;

        done--;
        if (bypass) {
            bypass = 0;

        }
        printf("%d is done... %d\n", player_id, done);


        while (done != 0) {
            printf("%d sees not all done... %d\n", player_id, done);
            sleep(1);
        }

        printf("\n");
    }

}

// updates num players, checks to see which player positions are null, etc...
void check_players() {

    int i;
    next_empty = -1;
    for (i = 0; i < 4; i++) {
        // this code for disconnected checking doesnt work.
        if (player_inputs[i*3] == 'q') {
            num_players--;
            next_empty = i;
            connected[i] = 0;
            printf("  %d has disconnected.\n", i);
        } else if (next_empty == -1 && !connected[i]) {
            next_empty = i;
            printf("  %d is the first unconnected player. Players now: %d\n", i, ++num_players);


        }
    }
}

