#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
#define MAX_ENEMY 15
extern enemy_t g_enemy_list[MAX_ENEMY];
#define MAX_MAGIC 20
magic_t g_magic_list[MAX_MAGIC];

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t g_enemy_list[MAX_ENEMY];

	for (int i = 0; i < 5; i++) {
		g_magic_list[i].type = 0;
		g_magic_list[i].pos_x = 0;
		g_magic_list[i].pos_y = 0;
		g_magic_list[i].size_w = 0;
		g_magic_list[i].size_h = 0;
		g_magic_list[i].velocity = 1.0;
		g_magic_list[i].target_ptr = &g_enemy_list[i];
	}
}