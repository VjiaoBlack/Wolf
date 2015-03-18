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


        *ent->bearing = atan2(m_player_pos[0]->y - ent->position->y, m_player_pos[0]->x - ent->position->x);

        float si = sin(*ent->bearing);
        float co = cos(*ent->bearing);

        // if (valid_move(ent->position, 1.5 * co, 1.5 * si, game_world)) {
            ent->position->x += 1.5 * co;
            ent->position->y += 1.5 * si;
        // }


    }
    // else, return
}
