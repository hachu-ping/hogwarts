#include "debug.h"
#include "enemy.h"
#include "fx.h"

explosion_t g_explosion_list[EXPLOSION_MAX_NUMBER];

void clear_explosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; ++i) {
		g_explosion_list[i].is_spawned = false;
	}
}

void create_explosion(double pos_x, double pos_y)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; i++) {
		// 비어 있는 슬롯 발견
		if (g_explosion_list[i].is_spawned == false) {
			g_explosion_list[i].pos_x = pos_x;
			g_explosion_list[i].pos_y = pos_y;
			g_explosion_list[i].current_frame = 0;
			
			g_explosion_list[i].is_spawned = true;

			DEBUG_PRINT("%d에 폭발 생성\n", i);
			return;
		}
	}

	//  모든 슬롯이 꽉 찼을 경우
	DEBUG_PRINT("[FX] 생성 실패! 사용 가능한 폭발 슬롯이 없습니다.\n");
}

void update_explosion(void)
{
	for (int i = 0; i < EXPLOSION_MAX_NUMBER; ++i) {
		if (g_explosion_list[i].is_spawned == true) {
			g_explosion_list[i].current_frame += 1;
			
			if (g_explosion_list[i].current_frame >= 16)
			{
				g_explosion_list[i].is_spawned = false;
				g_explosion_list[i].current_frame = 0;
			}
		}
	}
}