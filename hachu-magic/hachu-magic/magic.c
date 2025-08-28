

#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t g_magic_list[MAGIC_MAX_NUMBER];


void create_magic(int x, int y, int size_w, int size_h, float velocity, char type, enemy_t* target)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (g_magic_list[i].is_spawned == 0) {  // 비어 있는 슬롯 발견
			g_magic_list[i].pos_x = x;
			g_magic_list[i].pos_y = y;
			g_magic_list[i].size_w = size_w;
			g_magic_list[i].size_h = size_h;
			g_magic_list[i].velocity = velocity;
			g_magic_list[i].type = type;
			g_magic_list[i].target_ptr = (void*)target;

			//  진행 상황 로그 출력
			printf("[MAGIC] 슬롯 #%d에 마법 생성됨 (방향: %d, 속도: %.1f)\n", i, type, velocity);
			return;
		}
	}

	//  모든 슬롯이 꽉 찼을 경우
	printf("[MAGIC] 생성 실패! 사용 가능한 마법 슬롯이 없습니다.\n");
}

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (i > 5) {
			g_magic_list[i].is_spawned = 0;
		}

		g_magic_list[i].is_spawned = 1;
		g_magic_list[i].type = 0;
		g_magic_list[i].pos_x = 0;
		g_magic_list[i].pos_y = 0;
		g_magic_list[i].size_w = 20;
		g_magic_list[i].size_h = 20;
		g_magic_list[i].velocity = 1.0;
		g_magic_list[i].target_ptr = &g_enemy_list[i];
	}
}

void init_magic(void)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		g_magic_list[i].is_spawned = 0;
	}
}