#include <stdio.h>
#include <stdlib.h>

#include "mesh.h"
#include "line.h"

struct mesh {
    line** m_lines;
    int num_walls;
    int map_width;
    int map_height;
};

mesh *mesh_load_from_file(FILE *file) {
    char line_buf[256];

    mesh* walls = (mesh*) malloc(sizeof(mesh));

    float num, w, h;
    float x1, y1, x2, y2;

    fscanf(file, "%f %f %f\n", num, w, h);
    walls->num_walls = num;
    walls->map_width = w;
    walls->map_height = h;
    walls->m_lines = (line**) malloc(sizeof(line*) * num);

    int i = 0;

    while (fscanf(file, "%f %f %f %f\n", x1, y1, x2, y2)) {
        walls->m_lines[i] = new_line(x1, y1, x2, y2);
        i++;
    }
}

void free_mesh(mesh *m) {
    int i;
    for (i = 0; i < m->num_walls; i++) {
        free_line(m->m_lines[i]);
    }
    free(m);
}
