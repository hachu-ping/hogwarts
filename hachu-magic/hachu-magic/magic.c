#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t magics[15];

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t enemies[15];

	for (int i = 0; i < 5; i++) {
		magics[i].type = 0;
		magics[i].pos_x = 0;
		magics[i].pos_y = 0;
		magics[i].size_w = 0;
		magics[i].size_h = 0;
		magics[i].velocity = 1.0;
		magics[i].target_ptr = &enemies[i];
	}
}