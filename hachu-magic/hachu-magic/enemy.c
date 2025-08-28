#include <string.h>

#include "enemy.h"

enemy_t g_enemies[ENEMY_MAX_NUMBER];

void DEBUG_init_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		if (i > 5) {
			g_enemies[i].used = 0;
			continue;
		}
		g_enemies[i].type = 0;
		g_enemies[i].pos_x = 0;
		g_enemies[i].pos_y= 0;
		g_enemies[i].size_w = 40;
		g_enemies[i].size_h = 40;
		memcpy(g_enemies[i].pattern, "0123", sizeof(char) * 4);
		g_enemies[i].is_invincible = 0;
		g_enemies[i].life = 4;
		g_enemies[i].received_attack_count = 0;
		g_enemies[i].current_pattern= '0';
		g_enemies[i].used = 1;
		g_enemies[i].velocity = 1.0;
	}
}