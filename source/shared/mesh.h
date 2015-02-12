#ifndef MESH_H
#define MESH_H

#include <stdio.h>

#include "line.h"

/**
 * @file mesh.h
 * @author John Lekberg
 * @date 2015-02-11
 * @copyright MIT License
 * 
 * The mesh holds the static part of a level.
 */

typdef struct _mesh _mesh, *mesh;

/**
 * Loads and compiles a mesh from a given filestream. Returns NULL if there is
 * an error in loading the mesh.
 */
mesh mesh_load_from_file(FILE *file);

/**
 * Wraps to a call of `mesh_load_from_file` by checking if a file exists with
 * the name `filename`, and if it does exist then returns the mesh and returns
 * NULL if the named file doesn't exist.
 */
mesh mesh_load_from_filename(char *filename);

/**
 * Returns an array of lines stored in the mesh.
 */
line *mesh_lines(mesh m);
#endif
