#ifndef __FX_H__
#define __FX_H__

#include <stdbool.h>

#define EXPLOSION_MAX_NUMBER 60
#define EXPLOSION_FRAME_NUMBER 4
#define EXPLOSION_WIDTH 100
#define EXPLOSION_HEIGHT 100

typedef struct _explosion {
	// ���� ��ȿ�Ѱ�
	bool is_spawned;

	// ���� x ��ǥ (������� ����)
	double pos_x;

	// ���� y ��ǥ (������� ����)
	double pos_y;

	// ���� ������
	int current_frame;
} explosion_t;

extern explosion_t g_explosion_list[EXPLOSION_MAX_NUMBER];


void clear_explosion(void);
void create_explosion(double pos_x, double pos_y);
void update_explosion(void);

#endif /* __FX_H__ */


/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */