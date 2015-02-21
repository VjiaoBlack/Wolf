#ifndef WORLD_H
#define WORLD_H

#include "entity_store.h"
#include "../graphics/graphics_info.h"
#include "../audio/audio_info.h"
#include "../physics/physics_info.h"

/**
 * @file        world.h
 * @author      John Lekberg
 * @date        2015-02-11
 * @modified    2015-02-11
 * @copyright   MIT License
 *
 * The world is the main object of PW (Project Wolf). It contains a mesh
 * holding the static part of the level and a list of entities contained in the
 * world.
 */

typdef struct world {
    mesh          w_mesh;
    entity_store  w_entities;
    graphics_info w_graphics_info;
    audio_info    w_audio_info;
    physics_info  w_physics_info;
} world;

world *new_world();
void  free_world(world w);
#endif
