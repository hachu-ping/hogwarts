
#include "cat.h"

cat_t g_cat;

void DEBUG_init_cat(void) 
{
	// TODO: Modify to valid values
	g_cat.size_w = 200;
	g_cat.size_h = 200;
	g_cat.pos_x = 500;
	g_cat.pos_y = 500;
	g_cat.attack_delay = 0.2;
}