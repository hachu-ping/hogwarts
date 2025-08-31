#ifndef __CAT_H__
#define __CAT_H__

#include "enemy.h"

#define CAT_SIZE_W 200
#define CAT_SIZE_H 200
#define DEFAULT_ATTACK_COOLDOWN_TIME 0.2

typedef struct _cat {
	// ���� x ��ǥ (������� ����)
	double pos_x;

	// ���� y ��ǥ (������� ����)
	double pos_y;

	// ���� ����
	int size_w;

	// ���� ����
	int size_h;

	// ���� �ֱٿ� ������ �� �ð�
	double last_attack_time;

	// ���� ���ݱ��� �ɸ��� �ּ� �ð�
	double attack_cooldown_time;
} cat_t;


/*
 * ������� ���� ������ �� �ʱ�ȭ.
 */
void DEBUG_clear_cat(void);

/**
 * �������� ���� �ʱ�ȭ�մϴ�.
 */
void clear_cat(void);

/**
 * �������� ������ �� ������ �����մϴ�.
 * ������ ������ �� Ű �Է��� �ִٸ� ���� ���� ������ ����մϴ�.
 */
void update_cat();


/**
 * ���� �Է¿� ����, 
 * �� �Է� ������ ���� ���� �� ���� �տ� �ִ� ��ȿ�� ������ �������
 * ������ �����մϴ�.
 * @param magic_type �Է¿� ���� ������ �Է¹޽��ϴ�.
 */
void cast_magic(direction);

#endif /* __CAT_H__ */

