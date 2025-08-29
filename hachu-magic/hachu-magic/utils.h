#ifndef __UTILS_H__
#define __UTILS_H__

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>


/**
 * ù ��° ���ڷ� ���޵� ���� ��ȿ���� �˻��մϴ�. ���� �ش� ���� false (0) �̶�� description �� ����ϰ� ���α׷��� �����մϴ�.
 * @param test: ��ȿ�� �˻� ���
 * @param description : ����� ���� ��ȿ���� �ʴٸ� (0�̶��) �ش� �޽����� ���
 * @return void / ���� 0�̶�� ���α׷� ����
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

