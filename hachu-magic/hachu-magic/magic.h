#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>

typedef struct _magic {
	// TODO: change into enum (char)
	// type of magic (pattern?)
	char type;

	// current magic x position (center of magic)
	int pos_x;

	// current magic y position (center of magic)
	int pos_y;

	// magic width size
	int size_w;

	// magic height size
	int size_h;

	// magic movement velocity
	float velocity;

	// target's pointer. (cast into enemy_t* when use)
	void* target_ptr;

} magic_t;

/**
 * Initialize magic list's values.
 */
void DEBUG_init_magic(void);

#endif /* __MAGIC_H__ */
