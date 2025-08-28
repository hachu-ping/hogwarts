#ifndef __CAT_H__
#define __CAT_H__
#include "enemy.h"
typedef struct _cat {
	// ���� x��ǥ (�߾� ��ǥ)
	int pos_x;

	// ���� y��ǥ (�߾� ��ǥ)
	int pos_y;

	// ���� ����
	int size_w;

	// ���� ����
	int size_h;

	// ���� ��Ÿ�� (1.0 == 1 sec), ���� ��Ÿ�� üũ�� (�� ���� Allegro �ð�)
	double last_attack_time;

} cat_t;

void handle_input_and_create_magic(int);
void create_magic(int, int, int, int, float, char, enemy_t*);
void init_cat();
void update_cat();
void draw_cat();

/*
 * ������� ���� ����� �� �ʱ�ȭ
 */
void DEBUG_init_cat(void);

#endif /* __CAT_H__ */

