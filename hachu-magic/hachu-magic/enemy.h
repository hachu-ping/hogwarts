#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdbool.h>

typedef struct _enemy {
	// TODO: change into enum (char)
	// ���� ����
	int type;

	// ���� x��ǥ (�߾� ��ǥ)
	int pos_x;

	// ���� y��ǥ (�߾� ��ǥ)
	int pos_y;

	// ���� ����
	int size_w;

	// ���� ����
	int size_h;

	// �̵��ӵ�
	float velocity;

	// ���� �ִ� ü�� == ������ ���̿� ������
	int life;

	// ���� ���� ���� ���ط� == �ִ� ü�� - ���� ü��
	int received_attack_count;

	// TODO: change char type into enum
	// ���� ���� �迭. �迭 ��Ҵ� ����(����Ű)���� �����ȴ�.
	char pattern[15];
	
	// ���� ���� ù ��° ���� == pattern[received_attack_count]
	char current_pattern;

	// ���� ��ȿ�� �����ΰ�
	bool used;

	// ���� ������ �����ΰ�
	bool is_invincible;

} enemy_t;

/**
 * ������� ���� �� ����Ʈ �ʱ�ȭ
 */
void DEBUG_init_enemy(void);

#endif /* __ENEMY_H__ */
