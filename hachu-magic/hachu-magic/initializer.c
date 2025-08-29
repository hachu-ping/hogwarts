

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "enemy.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"

#define __DEBUG_MODE__ 0

extern unsigned char g_key[ALLEGRO_KEY_MAX];

void init_allegro(void)
{
	must_init(al_init(), "allegro");
}

void init_addons(void) 
{
	// png ????? ????? ???? ????? ?????
	must_init(al_init_image_addon(), "image addon init");

	// ??, ????, ??, ???? ?? ???????? ?????? ???? primitives ?????
	must_init(al_init_primitives_addon(), "primitives addon init");  

	//font addon initialize
	must_init(al_init_font_addon(), "font addon init");
	must_init(al_init_ttf_addon(), "ttf font addon init");

}

void install_driver(void)
{
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_install_mouse(), "mouse");
}

ALLEGRO_DISPLAY* init_display(const int width, const int height)
{
	ALLEGRO_DISPLAY* temp = al_create_display(width, height);
	must_init(temp, "display");

	return temp;
}
//시진 추가1

/*
ALLEGRO_FONT* init_builtin_font(void)
{
	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "font");

	return font;
}
*/
//시진 추가2


ALLEGRO_TIMER* init_timer(const double speed_secs)
{
	ALLEGRO_TIMER* temp = al_create_timer(speed_secs);
	must_init(temp, "timer");
	return temp;
}

ALLEGRO_EVENT_QUEUE* init_event_queue(void)
{
	ALLEGRO_EVENT_QUEUE* temp = al_create_event_queue();
	must_init(temp, "queue");
	return temp;
}

void init_data(void)
{
	memset(g_key, 0, sizeof(g_key));

	init_sprites();

#if __DEBUG_MODE__
	DEBUG_init_cat();
	DEBUG_init_enemy();
	DEBUG_init_magic();
#else
	init_cat();
	init_enemy();
	init_magic();
#endif	
}

