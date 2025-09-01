#include "debug.h"
#include "enemy.h"
#include "fx.h"

static explosion_t g_explosion_list[EXPLOSION_MAX_NUMBER];

const explosion_t* get_explosion_list(void)
{
	return &g_explosion_list;
}

void clear_explosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; ++i) {
		g_explosion_list[i].is_spawned = false;
	}
}

void create_explosion(double pos_x, double pos_y)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; i++) {
		// 빈자리 있는 슬롯 추가
		if (g_explosion_list[i].is_spawned == false) {
			g_explosion_list[i].pos_x = pos_x;
			g_explosion_list[i].pos_y = pos_y;
			g_explosion_list[i].current_frame = 0;
			
			g_explosion_list[i].is_spawned = true;

			DEBUG_PRINT("[FX] (%d, %d) explosions[%d]에 폭발 생성\n", pos_x, pos_y, i);
			return;
		}
	}

	//  빈자리가 더 없는 경우
	DEBUG_PRINT("[FX] 폭발 실패! 빈자리가 없어 폭발을 생성하지 못합니다.\n");
}

void update_explosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; ++i) {
		if (g_explosion_list[i].is_spawned == true) {
			g_explosion_list[i].current_frame += 1;
			
			if (g_explosion_list[i].current_frame >= EXPLOSION_DURATION_FRAME_NUMBER)
			{
				g_explosion_list[i].is_spawned = false;
				g_explosion_list[i].current_frame = 0;
			}
		}
	}
}