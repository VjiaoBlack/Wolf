#include "physics_handler.h"

int valid_move(vector2 *pos, int x_off, int y_off, world *w) {
    //initialize_terrain(w->w_mesh);
    vector2 *v = new_vector2(pos->x + x_off, pos->y + y_off);
    int b = is_open(v);
    free_vector2(v);
    //free_terrain();
    return b;
}
