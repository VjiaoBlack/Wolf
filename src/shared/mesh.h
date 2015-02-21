#ifndef MESH_H
#define MESH_H

#include <stdio.h>

#include "line.h"

/**
 * @file        mesh.h
 * @author      John Lekberg
 * @date        2015-02-11
 * @modified    2015-02-20 Victor Jiao
 * @copyright   MIT License
 *
 * The mesh holds the static part of a level.
 */

 typedef struct mesh mesh;

/**
 * Loads and compiles a mesh from a given filestream. Returns NULL if there is
 * an error in loading the mesh.
 */
mesh *mesh_load_from_file(FILE *file);

/**
 * Wraps to a call of `mesh_load_from_file` by checking if a file exists with
 * the name `filename`, and if it does exist then returns the mesh and returns
 * NULL if the named file doesn' exist.
 */
mesh *mesh_load_from_filename(char *filename);

/**
 * Destroys a mesh.
 */
void free_mesh(mesh *m);

/**
 * Iterates over every line and applies an action. The ordering is undefined.
 */
void mesh_for_each_line(mesh *m, void (*function)(line*));

#endif
