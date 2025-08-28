#include <string.h>

#include "enemy.h"

enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

void DEBUG_init_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		if (i > 5) {
			g_enemy_list[i].is_spawned = 0;
			continue;
		}
		g_enemy_list[i].type = 0;
		g_enemy_list[i].pos_x = 0;
		g_enemy_list[i].pos_y= 0;
		g_enemy_list[i].size_w = 40;
		g_enemy_list[i].size_h = 40;
		memcpy(g_enemy_list[i].pattern, "0123", sizeof(char) * 4);
		g_enemy_list[i].is_invincible = 0;
		g_enemy_list[i].life = 4;
		g_enemy_list[i].received_attack_count = 0;
		g_enemy_list[i].current_pattern= '0';
		g_enemy_list[i].is_spawned = 1;
		g_enemy_list[i].velocity = 1.0;
	}
}

void init_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		g_enemy_list[i].is_spawned = 0;
	}
}