

#include <allegro5/allegro_font.h>
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

extern unsigned char key[ALLEGRO_KEY_MAX];

void init_allegro(void)
{
	must_init(al_init(), "allegro");
}

void init_addons(void) 
{
	// png 이미지 활용을 위한 이미지 에드온
	must_init(al_init_image_addon(), "image addon init");

	// 선, 사각형, 원, 선분 등 기초적인 도형을 위한 primitives 에드온
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

void init_data(void)
{
	memset(key, 0, sizeof(key));

	init_sprites();

	init_cat();
	DEBUG_init_enemy();
	DEBUG_init_magic();
}

