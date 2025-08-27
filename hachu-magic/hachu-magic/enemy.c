#include <string.h>

#include "enemy.h"
// TODO: define max enemy number
enemy_t enemies[15];

void DEBUG_init_enemy(void) {
	for (int i = 0; i < 5; i++) {
		enemies[i].type = 0;
		enemies[i].pos_x = 0;
		enemies[i].pos_y= 0;
		enemies[i].size_w = 0;
		enemies[i].size_h = 0;
		memcpy(enemies[i].pattern, "0123", sizeof(char) * 4);
		enemies[i].is_invincible = 0;
		enemies[i].life = 4;
		enemies[i].received_attack_count = 0;
		enemies[i].current_pattern= '0';
		enemies[i].used = 1;
		enemies[i].velocity = 1.0;
	}
}