#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include <allegro5/allegro5.h>

#define KEY_SEEN     1
#define KEY_DOWN     2

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

typedef enum _magic_type {
    MAGIC_TYPE_NONE   = 0,
    MAGIC_TYPE_FIRE   = 1,
    MAGIC_TYPE_WATER  = 2,
    MAGIC_TYPE_AIR    = 3,
    MAGIC_TYPE_NATURE = 4
} magic_type;

typedef enum _direction {
    DIRECTION_NONE  = 0,
    DIRECTION_LEFT  = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP    = 3,
    DIRECTION_DOWN  = 4
} direction;


/**
 * Ű���� �Է¿� ���� �������� g__key[]�� ���� �� ��ȣ�� ���� Ű������ �Է� ���θ� ������Ʈ�մϴ�.
 * @param event: ALLEGRO_EVENT* �� ���� �̺�Ʈ �Է��� �����մϴ�.
 */
void keyboard_update(ALLEGRO_EVENT* event);

#endif /* __GAME_SYSTEM_H__ */

