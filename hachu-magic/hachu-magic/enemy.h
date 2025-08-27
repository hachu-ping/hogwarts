#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdbool.h>

typedef struct _enemy {
	// TODO: change into enum (char)
	// type of enemy
	int type;

	// current enemy x position (center of enemy)
	int pos_x;

	// current enemy y position (center of enemy)
	int pos_y;

	// enemy width size
	int size_w;

	// enemy height size
	int size_h;

	// enemy movement velocity
	float velocity;

	// enemy's max life count == length of pattern
	int life;
	// enemy's received attack count == left life
	int received_attack_count;

	// TODO: change char type into enum
	// enemy's pattern array. pattern consist of magic_types(arrow)
	char pattern[15];
	
	// current first pattern == pattern[received_attack_count]
	char current_pattern;

	// is enemy valid
	bool used;

	// enemy doesn't be target of attack when is_invincible is true
	bool is_invincible;

	// 
} enemy_t;

/**
 * Initialize enemy list's values.
 */
void DEBUG_init_enemy(void);

#endif /* __ENEMY_H__ */
