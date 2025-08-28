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

	// ���������� ������ �ð�
	double last_attack_time;

} cat_t;

/**
 * ������� ���� ����� �� �ʱ�ȭ
 */
void init_cat(void);

void magic_attack(int, int, int);
void init_cat();
void update_cat();
void draw_cat();

#endif /* __CAT_H__ */