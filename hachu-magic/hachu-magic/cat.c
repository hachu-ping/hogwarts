
#include "cat.h"

CAT_T g_cat;

void init_cat() 
{
	// TODO: Modify to valid values
	g_cat.size_w = 200;
	g_cat.size_h = 200;
	g_cat.pos_x = 500;
	g_cat.pos_y = 500;
	g_cat.attack_delay = 0.2;
}