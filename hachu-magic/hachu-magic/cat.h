#ifndef __CAT_H__
#define __CAT_H__

typedef struct _cat {
	// ���� x��ǥ (�߾� ��ǥ)
	int pos_x;

	// ���� y��ǥ (�߾� ��ǥ)
	int pos_y;

	// ���� ����
	int size_w;

	// ���� ����
	int size_h;

	// ���� ��Ÿ�� (1.0 == 1 sec)
	float attack_delay;

} cat_t;

/**
 * ������� ���� ����� �� �ʱ�ȭ
 */
void DEBUG_init_cat(void);

#endif /* __CAT_H__ */