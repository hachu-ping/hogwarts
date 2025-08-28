#ifndef __UTILS_H__
#define __UTILS_H__

#include <allegro5/allegro5.h>

#include <stdbool.h>


#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>



/**
 * ù ��° ���ڷ� ���޵� ���� ��ȿ���� �˻��մϴ�. ���� �ش� ���� false (0) �̶�� description �� ����ϰ� ���α׷��� �����մϴ�.
 * @param test: ��ȿ�� �˻� ���
 * @param description : ����� ���� ��ȿ���� �ʴٸ� (0�̶��) �ش� �޽����� ���
 * @return void / ���� 0�̶�� ���α׷� ����
 */
void must_init(bool, const char*);
void keyboard_update(ALLEGRO_EVENT*);
void magic_attack(int, int, int);
void cat_init();
void cat_update();
void cat_draw();


#endif /* __UTILS_H__ */



/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */
