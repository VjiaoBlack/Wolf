#ifndef WORLD_H
#define WORLD_H

// #include "entity_store.h"   // we dont have this file??/
#include "../shared/mesh.h"
#include "../shared/entity.h"

/**
 * @file        world.h
 * @author      John Lekberg
 * @date        2015-02-11
 * @modified    2015-02-20 Victor Jiao
 * @copyright   MIT License
 *
 * The world is the main object of PW (Project Wolf). It contains a mesh
 * holding the static part of the level and a list of entities contained in the
 * world.
 */

struct entity;
struct entity_store;

typedef struct world {
    mesh*          w_mesh;
    struct entity_store*  w_store;
    // graphics_info w_graphics_info;
    // audio_info    w_audio_info;
    // physics_info  w_physics_info;
} world;

world *new_world();
void  free_world(world* w);
#endif
