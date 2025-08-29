#include "debug.h"

int max_stage_number = 2;
int current_stage = 0;

int stage_wave_max_number[] = { 2, 3, 4 };
int current_wave = 0;

int stage_wave_spawn_enemy_number[] = { 5, 6, 7 };

int life = 5;

void apply_damage(int damage)
{
	life -= damage;

	DEBUG_PRINT("충돌 발생 life -> %d\n", life);

	if (life <= 0) {
		// TODO: 게임오버 처리하기
		DEBUG_PRINT("게임 오버\n");
	}
}