#ifndef __FX_H__
#define __FX_H__

#include <stdbool.h>

#define EXPLOSION_MAX_NUMBER 60
#define EXPLOSION_DURATION_FRAME_NUMBER 16
#define EXPLOSION_WIDTH 100
#define EXPLOSION_HEIGHT 100

typedef struct _explosion {
	// 폭발 활성화여부
	bool is_spawned;

	// 폭발 x 좌표 (화면에서 중심)
	double pos_x;

	// 폭발 y 좌표 (화면에서 중심)
	double pos_y;

	// 폭발 프레임
	int current_frame;
} explosion_t;

const explosion_t* get_explosion_list(void);

extern explosion_t g_explosion_list[EXPLOSION_MAX_NUMBER];

/**
 * explosions 배열의 is_spawned 상태 초기화합니다.
 */
void clear_explosion(void);

/**
 * 주어진 (x, y) 좌표에 폭발 이펙트를 생성합니다. 
 * 현재 활성화된 폭발 이펙트가 최대치 개수를 넘어간 경우, 
 * 이펙트가 생성되지 않을 수 있습니다.
 * @param pos_x: 폭발 이펙트가 생성될 x 좌표
 * @param pos_y: 폭발 이펙트가 생성될 y 좌표
 */
void create_explosion(double pos_x, double pos_y);

/**
 * 폭발 이펙트의 프레임을 업데이트하고,
 * 시간이 지난 폭발 이펙트를 explosions 배열에서 소멸시킵니다.
 */
void update_explosion(void);

#endif /* __FX_H__ */