#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t g_magics[15];

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t g_enemies[15];

	for (int i = 0; i < 5; i++) {
		g_magics[i].type = 0;
		g_magics[i].pos_x = 0;
		g_magics[i].pos_y = 0;
		g_magics[i].size_w = 0;
		g_magics[i].size_h = 0;
		g_magics[i].velocity = 1.0;
		g_magics[i].target_ptr = &g_enemies[i];
	}
}