#ifndef ENTITY_H
#define ENTITY_H

#include "../shared/world.h"
#include "../shared/mesh.h"

/**
 * @file      entity.h
 * @author    John Lekberg
 * @date      2015-02-11
 * @modified  2015-02-11
 * @copyright MIT Licsense
 *
 * An entity is a dynamic object with:
 *   - Physics  component.
 *   - Graphics component.
 *   - Audio    component.
 */

// NOTE: when you free an entity, dont shift array. just keep going.
// I created a new kinda data structure to handle this well.
// Ask me if you want more specs.

struct world;

typedef enum {Player, NPC} Kind;

typedef struct entity {
    int ID;

    Kind kind;
    int health;
    vector2 *position;
    float* bearing;
    mesh *e_mesh;

    // graphics_handler e_graphics_handler;
    // physics_handler  e_physics_handler;
    // audio_handler    e_audio_handler;
    // input_handler    e_input_handler;
} entity;

typedef struct int_node {
    int value;
    struct int_node *next;
} int_node;

typedef struct entity_store {
    entity** entities;
    int num_entities;
    int_node* open_spots;
} entity_store;

// enemy hp (if 'false', is dead);
int damage(entity *a, int dmg);

int add_new_entity(int health, struct world* worl, Kind kind, vector2* pos, float* dir);

void free_entity(entity *ent, entity_store* store);

entity_store* create_entity_store();

void free_entity_store(entity_store* store);

int_node* remove_node(int_node* node);

int_node* push_node(int_node* node);


/**
 * Iterates over every entity and applies an action. The ordering is undefined.
 */
void for_each_entity(entity_store *, void (*function)(entity*));

#endif

