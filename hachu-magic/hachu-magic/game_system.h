#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include <allegro5/allegro5.h>

#define KEY_SEEN     1
#define KEY_DOWN     2

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800


/**
 * Ű���� �Է¿� ���� �������� g__key[]�� ���� �� ��ȣ�� ���� Ű������ �Է� ���θ� ������Ʈ�մϴ�.
 * @param event: ALLEGRO_EVENT* �� ���� �̺�Ʈ �Է��� �����մϴ�.
 */
void keyboard_update(ALLEGRO_EVENT* event);

#endif /* __GAME_SYSTEM_H__ */

