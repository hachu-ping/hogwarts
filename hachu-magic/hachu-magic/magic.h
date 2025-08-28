
#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>
#include <math.h>

#define MAGIC_MAX_NUMBER 15

typedef struct _magic {
	// ��ȿ�� �������ΰ�
	char is_spawned;

	// TODO: change into enum (char)
	// ������ ���� (����)
	char type;

	// ���� ���� źȯ�� x��ǥ (�߾� ��ǥ)
	double pos_x;

	// ���� ���� źȯ�� y��ǥ (�߾� ��ǥ)
	double pos_y;

	// ���� źȯ�� ���� ����
	int size_w;

	// ���� źȯ�� ���� ����
	int size_h;

	// ���� źȯ�� �̵��ӵ�
	float velocity;

	// Ÿ��(��)�� �ּҰ�. ��� �� (enemy_t* �� ĳ�����Ͽ� ���)
	void* target_ptr;

} magic_t;

/**
 * ������� ���� ����źȯ ��� �ʱ�ȭ
 */
void DEBUG_init_magic(void);

/**
 * ������ ����� ��� magics ����Ʈ�� �ʱ�ȭ�մϴ�.
 */
void init_magic(void);

void move_magic(void);

#endif /* __MAGIC_H__ */
