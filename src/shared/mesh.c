#include <stdio.h>
#include <stdlib.h>

#include "mesh.h"
#include "line.h"

struct mesh {
    line** m_lines;
};

mesh *mesh_load_from_file(FILE *file) {
    double length, x0, y0, x1, y1;
    mesh* result = (mesh*)malloc(sizeof(mesh));
    fscanf(file, "%ud", &length);
    result->m_lines = (line**)calloc(length, sizeof(line*));
    for (int i = 0; i != length; ++i) {
        fscanf(file, "%d %d %d %d", &x0, &y0, &x1, &y1);
        m_lines[i] = new_line(x0, y0, x1, y1);
    }
    return result;
}
