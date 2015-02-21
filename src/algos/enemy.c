#include "../algos/enemy.h"



void update_enemy(entity* ent) {

    // only run this for NPCs
    if (ent->kind == NPC) {
        // you have :
        //      world* game_world
        //      entity* ent
        //      vector2* player_pos
        //      float* player_angle
        // maybe more...
        // do something!!!



        *ent->bearing = atan2(player_pos->y - ent->position->y, player_pos->x - ent->position->x);

        float si = sin(*ent->bearing);
        float co = cos(*ent->bearing);

        ent->position->y += 1.5 * si;
        ent->position->x += 1.5 * co;



    }
    // else, return
}
