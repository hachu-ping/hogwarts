
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keycodes.h>
#include <stdio.h>

#include "debug.h"
#include "enemy.h"
#include "utils.h"
#include "magic.h"

#define KEY_SEEN     1
#define KEY_DOWN     2

void must_init(bool test, const char* description) 
{
    if (test) return;
    DEBUG_PRINT("couldn't initialize %s\n", description);
    exit(1);
}

direction_t keycode_to_direction(char keycode)
{
    switch (keycode) {
    case ALLEGRO_KEY_LEFT:  return DIRECTION_LEFT;
    case ALLEGRO_KEY_RIGHT: return DIRECTION_RIGHT;
    case ALLEGRO_KEY_UP:    return DIRECTION_UP;
    case ALLEGRO_KEY_DOWN:  return DIRECTION_DOWN;
    default:                return DIRECTION_NONE;
    }
}

magic_type_t direction_to_magic_type(direction_t direction)
{
    switch (direction) {
    case DIRECTION_LEFT:    return MAGIC_TYPE_FIRE;
    case DIRECTION_RIGHT:   return MAGIC_TYPE_WATER;
    case DIRECTION_UP:      return MAGIC_TYPE_AIR;
    case DIRECTION_DOWN:    return MAGIC_TYPE_NATURE;
    default:                return MAGIC_TYPE_NONE;
    }
}
