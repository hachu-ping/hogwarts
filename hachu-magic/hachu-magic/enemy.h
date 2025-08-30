

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdbool.h>

#define ENEMY_MAX_NUMBER 15

static const int ENEMY_WIDTH[] = { 140, 180, 220, 320 };
static const int ENEMY_HEIGHT[] = { 140, 180, 220, 320 };

typedef struct _enemy {
	// TODO: change into enum (char)
	// ���� ����
	int type;

	// ���� x��ǥ (�߾� ��ǥ)
	double pos_x;

	// ���� y��ǥ (�߾� ��ǥ)
	double pos_y;

	// ���� ����
	double size_w;

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
	bool is_spawned;

	// ���� ������ �����ΰ�
	bool is_invincible;

} enemy_t;

/**
 * ������� ���� �� ����Ʈ �ʱ�ȭ
 */
 void DEBUG_init_enemy(void);

/**
 * ���� ����� ��� enemies ����Ʈ�� �ʱ�ȭ�մϴ�.
 */
void init_enemy(void);

/**
 * ���� �������� ������ ���� ���� �����ϰ� ������ �ʱ�ȭ�մϴ�. 
 */
void spawn_enemy(void);

/**
 * ���� Ȱ��ȭ�� ���� ������ �˻��մϴ�. 
 * ��� ���� ���� (��Ȱ��ȭ ��) ��� true�� ��ȯ�մϴ�.
 * @return bool: ��ü ���� ��Ȱ��ȭ ����
 */
bool is_enemy_cleared(void);

/**
 * Ư�� ���� ���� ����̿��� �浹 ���θ� �˻��մϴ�.
 * @param enemy_ptr: �浹���θ� �˻��Ϸ��� �� ����ü�� ���� ������
 * @return bool: �浹 ����
 */
bool is_collided_with_cat(enemy_t* enemy_ptr);

/**
 * ���� Ȱ��ȭ�� ������ ����̿��� �浹�� ���� �˻��մϴ�.
 * �浹�� �߻��� ���, �浹�� �߻������� ���ӸŴ������� �˸��ϴ�.
 */
void handle_enemy_collision(void);

#endif /* __ENEMY_H__ */
