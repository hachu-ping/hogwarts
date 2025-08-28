#ifndef __UTILS_H__
#define __UTILS_H__

#include <allegro5/allegro5.h>

#include <stdbool.h>


#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>





void must_init(bool, const char*);
void keyboard_update(ALLEGRO_EVENT*);
void handle_input_and_create_magic(int);

/*
void create_magic(int, int, int, int, float, char, enemy_t*);
void init_cat();
void update_cat();
void draw_cat();
*/


typedef enum {
    DIR_NONE = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
    DIR_UP = 3,
    DIR_DOWN = 4
} Direction;

Direction keycode_to_direction(int);

#endif /* __UTILS_H__ */



/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */

