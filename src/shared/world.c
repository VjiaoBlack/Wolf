#include "world.h"

world *new_world() {
    world *worl = (world*) malloc(sizeof(world));

    FILE* map = fopen("tools/map_visualizer/test.map", "r");
    printf("woah\n");
    worl->w_mesh = mesh_load_from_file(map);
    printf("asdf\n");
    return worl;
}

void free_world(world* w) {
    free_mesh(w->w_mesh);

    free(w);
}
