#include "wolf.h"

int main(int argc, char** argv) {

    printf("-~Wolf~-\n");

    start();

}

void start() {
    char c[2];
    printf("Start? (y|n): ");
    fgets(c,2,stdin);

    switch( *c ) {
        case 'n':
            while (getchar() != '\n');
            printf("\nGoodbye.\n");
            exit(0);
            break;
        case 'y':
            while (getchar() != '\n');
            printf("\nStarting game...\n");
            break;
        default:
            while (getchar() != '\n');
            start();
            break;
    }
}
