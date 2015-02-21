#include "world.h"

world *new_world() {
    world *worl = (world*) malloc(sizeof(world));

    FILE* map = fopen("res/testmap.map", "r");

    if (map == NULL) {
        printf("Invalid map file: check tools/map_visualizer/testmap.map\n");
    }

    worl->w_mesh = mesh_load_from_file(map);
    return worl;
}

void free_world(world* w) {
    free_mesh(w->w_mesh);

    free(w);
}
