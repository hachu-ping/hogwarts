#ifndef __UTILS_H__
#define __UTILS_H__

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>


/**
 * 첫 번째 인자로 전달된 값의 유효성을 검사합니다. 만약 해당 값이 false (0) 이라면 description 을 출력하고 프로그램을 종료합니다.
 * @param test: 유효성 검사 대상
 * @param description : 대상의 값이 유효하지 않다면 (0이라면) 해당 메시지를 출력
 * @return void / 값이 0이라면 프로그램 종료
 */
void must_init(bool, const char*);
void keyboard_update(ALLEGRO_EVENT*);
void cast_magic_and_create_magic(int);

/*
void create_magic(int, int, int, int, float, char, enemy_t*);
void init_cat();
void update_cat();
void draw_cat();
*/


typedef enum _direction {
    DIRECTION_NONE = 0,
    DIRECTION_LEFT = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP = 3,
    DIRECTION_DOWN = 4
} direction;

direction keycode_to_direction(int);

#endif /* __UTILS_H__ */



/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */

