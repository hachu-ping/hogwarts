

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"

extern unsigned char g_key[ALLEGRO_KEY_MAX];

void init_allegro(void)
{
	must_init(al_init(), "allegro");
}

void init_addons(void) 
{
	// PNG 이미지를 사용하기 위한 image addon 추가
	must_init(al_init_image_addon(), "image addon init");

	// 기하체 그리기 위한 primitives addon 추가
	must_init(al_init_primitives_addon(), "primitives addon init");  
}

void install_driver(void)
{
	must_init(al_install_keyboard(), "keyboard");
}

ALLEGRO_DISPLAY* init_display(const int width, const int height)
{
	ALLEGRO_DISPLAY* temp = al_create_display(width, height);
	must_init(temp, "display");

	return temp;
}

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

void init_keyboard(void)
{
	memset(g_key, 0, sizeof(g_key));
}


void init_data(void)
{
	init_keyboard();
	init_sprites();

#ifdef DEBUG_MODE
	DEBUG_init_cat();
	DEBUG_init_enemy();
	DEBUG_init_magic();
	clear_explosion();
#else
	init_cat();
	init_enemy();
	init_magic();
	clear_explosion();
#endif	
}

