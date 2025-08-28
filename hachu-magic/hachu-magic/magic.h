#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>



typedef struct _magic {
	// TODO: change into enum (char)
	// ������ ���� (����)
	char type;

	// ���� ���� źȯ�� x��ǥ (�߾� ��ǥ)
	int pos_x;

	// ���� ���� źȯ�� y��ǥ (�߾� ��ǥ)
	int pos_y;

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

#endif /* __MAGIC_H__ */
