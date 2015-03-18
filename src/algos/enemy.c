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


        if (ent->health < 0) {
            // free_entity(ent, game_world->w_store);
            ent->position->x = 300;
            ent->position->y = 300;
            ent->health = 100;

            float* angle = malloc(sizeof(float));
            add_new_entity(100,game_world,NPC,new_vector2(100,100),angle, -1);

        }


        int asdf;

        int min;

        float dist = 999.9;
        float cur_dist = 0.0;

        // figure out closest enemy;
        for (asdf = 0; asdf < 4; asdf++) {
            if (connected[asdf] > 0) {
                // printf("what%d\n", asdf);
                if (  (cur_dist = distance(ent->position, m_player_pos[asdf])) <= dist) {
                    // printf("omgg\n");
                    min = asdf;
                }
            }
        }
        // printf("atan\n");

        *ent->bearing = atan2(m_player_pos[min]->y - ent->position->y, m_player_pos[min]->x - ent->position->x);



        // printf("asdf\n");


        float si = sin(*ent->bearing);
        float co = cos(*ent->bearing);

        if (valid_move(ent->position, 1 * co, 1 * si, game_world)) {

            int i = 0;
            int j = 0;
            while (j < game_world->w_store->num_entities) {
                if (game_world->w_store->entities[i] != NULL) {
                    entity *targ = game_world->w_store->entities[i];
                    // decreaese enemy hp if connected.
                    if (targ->kind == Player &&
                        abs(targ->position->x - ent->position->x) < 10 &&
                        abs(targ->position->y - ent->position->y) < 10) {

                        targ->health -= 1;

                        if (targ->health < 0) {
                            free_entity(targ, game_world->w_store);
                        }
                        break;
                    }


                    j++;

                }
                i++;
            }




            ent->position->x += 1 * co;
            ent->position->y += 1 * si;
        }


    }
    // else, return
}

void update_bullet(entity* ent) {
    // printf("updating bulet\n");
    if (ent->kind == Bullet) {
        // you have :
        //      world* game_world
        //      entity* ent
        //      vector2* player_pos
        //      float* player_angle
        // maybe more...
        // do something!!!


        // *ent->bearing = atan2(m_player_pos[0]->y - ent->position->y, m_player_pos[0]->x - ent->position->x);

        float si = sin(*ent->bearing);
        float co = cos(*ent->bearing);

        if (valid_move(ent->position, 3 * co, 3 * si, game_world)) {
            if (ent->position->x < 0 || ent->position->x > 1000 || ent->position->y < 0 || ent->position->y > 700) {
                free_entity(ent, game_world->w_store);
                shot[ent->multi_id] = 0;
            }

            ent->position->x += 5 * co;
            ent->position->y += 5 * si;


            int i = 0;
            int j = 0;
            int continu = 0;
            while (j < game_world->w_store->num_entities) {
                if (game_world->w_store->entities[i] != NULL) {
                    entity *targ = game_world->w_store->entities[i];
                    // decreaese enemy hp if connected.
                    if (targ->kind == NPC &&
                        abs(targ->position->x - ent->position->x) < 10 &&
                        abs(targ->position->y - ent->position->y) < 10) {

                        targ->health -= 20;
                        free_entity(ent, game_world->w_store);
                        shot[ent->multi_id] = 0;
                        continu = 1;
                        break;
                    }


                    j++;

                }
                i++;
            }



        } else {
            // printf("freeing ent\n");
            free_entity(ent, game_world->w_store);
            // printf("freed ent\n");

            shot[ent->multi_id] = 0;
        }


    }
}
