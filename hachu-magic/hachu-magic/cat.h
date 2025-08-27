#ifndef __CAT_H__
#define __CAT_H__

typedef struct _cat {
	// current cat x position (center of cat)
	int pos_x;

	// current cat y position (center of cat)
	int pos_y;

	// cat width size
	int size_w;

	// cat height size
	int size_h;

	// time between every attacks (1.0 == 1 sec)
	float attack_delay;

} cat_t;

/**
 * Initialize cat's values.
 */
void DEBUG_init_cat(void);

#endif /* __CAT_H__ */