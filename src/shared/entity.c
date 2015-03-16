#include "entity.h"


int damage(entity *a, int dmg) {
    return (a->health -= dmg);
}

entity* add_new_entity(int health, world* worl, Kind kind, vector2* pos, float* dir, int multi_id) {

    entity *ent = malloc(sizeof(entity));
    if (worl->w_store->open_spots) {
        ent->ID = worl->w_store->open_spots->value;
        worl->w_store->open_spots = remove_node(worl->w_store->open_spots);
        worl->w_store->num_entities++;
    } else {
        ent->ID = worl->w_store->num_entities++;
    }

    ent->kind = kind;
    ent->health = health;
    ent->position = pos;
    ent->bearing = dir;
    ent->e_mesh = worl->w_mesh;
    ent->multi_id = multi_id;

    worl->w_store->entities = (entity**) realloc(worl->w_store->entities, sizeof(entity*) * worl->w_store->num_entities);

    worl->w_store->entities[ent->ID] = ent;
    return ent;
}

void free_entity(entity* ent, entity_store* store) {
    free(ent->position);
    free(ent->position);
    store->num_entities--;

    int_node* node = (int_node*) malloc(sizeof(int_node));
    node->value = ent->ID;
    node->next = store->open_spots;
    store->open_spots = node;

    // cant free the mesh... lol.

    free(ent);
}

entity_store* create_entity_store() {
    entity_store* entities = (entity_store*) malloc(sizeof(entity_store));
    entities->num_entities = 0;
    entities->open_spots = NULL;
    return entities;
}

void free_entity_store(entity_store* store) {
    int i = 0;
    int j = 0;
    while (j < store->num_entities) {
        if (store->entities[i]) {
            free(store->entities[i]);
            j++;
        }
        i++;
    }
    free(store->entities);
    free(store->open_spots);
    free(store);

}

int_node* remove_node(int_node* node) {
    int_node* res = node->next;
    free(node);
    return res;
}



void for_each_entity(entity_store *store, void (*function)(entity*)) {
    int i = 0;
    int j = 0;
    while (j < store->num_entities) {
        if (store->entities[i]) {
            (*function)(store->entities[i]);
            j++;
        }
        i++;
    }
}
