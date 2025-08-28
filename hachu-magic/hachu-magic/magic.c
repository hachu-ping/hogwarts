#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t g_magics[MAGIC_MAX_NUMBER];

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t g_enemies[ENEMY_MAX_NUMBER];

	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		if (i > 5) {
			g_magics[i].is_spawned = 0;
		}

		g_magics[i].is_spawned = 1;
		g_magics[i].type = 0;
		g_magics[i].pos_x = 0;
		g_magics[i].pos_y = 0;
		g_magics[i].size_w = 20;
		g_magics[i].size_h = 20;
		g_magics[i].velocity = 1.0;
		g_magics[i].target_ptr = &g_enemies[i];
	}
}

void init_magic(void)
{
	for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
		g_magics[i].is_spawned = 0;
	}
}