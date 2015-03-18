#include "physics_info.h"


/*
 *  initalizes all of the walls of the mesh as a collection of points (obstacles)
 */
void initialize_terrain(mesh *m) {
    line **lines = m->m_lines;
    int line_num = m->num_walls;
    int num_obst = 0;
    for (int i = 0; i < line_num; ++i) {
        vector2 *start = lines[i]->position1;
        vector2 *end = lines[i]->position2;
        float length = distance(start, end);
        num_obst += (int) length/RADIUS*CIRCLES_PER_RADIUS + 2;
    }

    // printf("Number of circles: %d\n", num_obst);
    ter = (terrain *) malloc(sizeof(terrain));
    ter->obstacles = (vector2 **) calloc(sizeof(vector2 *), num_obst);
    ter->num_obstacles = 0;


    int index = 0;
    for (int i = 0; i < line_num; ++i) {
        vector2 *start = lines[i]->position1;
        vector2 *end = lines[i]->position2;
        float ang = angle(start, end);
        float length = distance(start, end);
        float x_weight = cos(ang);
        float y_weight = sin(ang);
        int num_circs = (int) length/RADIUS*CIRCLES_PER_RADIUS + 2;
        float step_size = length/(num_circs-1);
        // printf("Making wall from (%f, %f) to (%f, %f)\n", start->x, start->y, end->x, end->y);
        // printf("(x_weight, y_weight): (%f, %f)\n", x_weight, y_weight);
        for (int j = 0; j < num_circs; ++j) {
            ter->obstacles[index] = new_vector2(start->x + j * step_size * x_weight, start->y + j * step_size * y_weight);
            // printf("Added circle at (%f, %f)\n", start->x + j * step_size * x_weight, start->y + j * step_size * y_weight);
            ter->num_obstacles++;
            ++index;
        }
    }
}

/*
 *  checks whether location loc is near an obstacle
 */
int is_open(vector2 *loc) {
    for (int i = 0; i < ter->num_obstacles; ++i)
        //change to "square_distance" to change shape from circle to square
        if (distance(loc, ter->obstacles[i]) < RADIUS)
            return 0;
    return 1;
}

/*
 *  frees up memory space from terrain
 */
void free_terrain(){
    for (int i = 0; i < ter->num_obstacles; ++i)
        free_vector2(ter->obstacles[i]);
    free(ter);
}
