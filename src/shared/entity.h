#ifndef ENTITY_H
#define ENTITY_H

#include "../graphics/graphics_handler.h"
#include "../physics/physics_handler.h"
#include "../audio/audio_handler.h"
#include "../input/input_handler.h"

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

typedef struct entity {
    int ID;
    graphics_handler e_graphics_handler;
    physics_handler  e_physics_handler;
    audio_handler    e_audio_handler;
    input_handler    e_input_handler;
    vector2          coordinates;
} entity;
#endif
