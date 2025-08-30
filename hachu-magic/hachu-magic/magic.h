
#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>
#include <math.h>

#include "game_system.h"

#define MAGIC_MAX_NUMBER 15
#define MAGIC_WIDTH 100
#define MAGIC_HEIGHT 100

typedef struct _magic {
	// ���� ������ ��ȿ�Ѱ�
	char is_spawned;

	// ������ ����
	magic_type_t type;

	// ���� x ��ǥ (������� ����)
	double pos_x;

	// ���� y ��ǥ (������� ����)
	double pos_y;

	// ���� ����
	int size_w;

	// ���� ����
	int size_h;

	// ���� �̵� �ӵ�
	double velocity;

	// ������ ���� ���ư��� ���� ���� ������.
	// ����� �� (enemy_t*)�� ĳ�����Ͽ� ���.
	void* target_ptr;

} magic_t;

/**
 * ����� ������ ������ ���� ��ȯ�� �� ���
 */
void DEBUG_clear_magic(void);

/**
 * magic �迭�� is_spawned ���� �ʱ�ȭ�մϴ�.
 */
void clear_magic(void);

/**
 * ����ִ� magic ���Կ� ������ �ʱⰪ�� �ֽ��ϴ�.
 * @param pos_x: ������ �����ϰ��� �ϴ� x��ǥ
 * @param pos_y: ������ �����ϰ��� �ϴ� x��ǥ
 * @param type: ������ ���� Ÿ��
 * @param target: ������ ��ǥ(��)�� ���� ������
 */
void create_magic(double pos_x, double pos_y, magic_type_t type, enemy_t* target);

/**
 * Ÿ�ٰ��� �浹�� ���� �˻��մϴ�.
 * �浹 ����� ������ ������ �ִ� target(enemy_t*) �� ������ Ȱ���մϴ�.
 * @param magic_ptr: ���� ����ü�� �ּҰ�
 * @return �浹���� boolean
 */
bool is_collided_with_target(magic_t* magic_ptr);

/**
 * ���� ��ȯ�� ��� ������ �浹�� �˻��ϰ�, 
 * Ÿ�� ������ �浹�� �浹�� ���� ó���� �����մϴ�.
 */
void handle_magic_collision(void);

/**
 * ���� �����ӿ� ���� Ȱ��ȭ�� ��� ������ �̵���ŵ�ϴ�.
 */
void move_magic(void);

#endif /* __MAGIC_H__ */
