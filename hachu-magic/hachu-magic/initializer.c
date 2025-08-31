

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "audio.h"
#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
#include "initializer.h"
#include "game_system.h"
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
//?���? 추�??1

/*
ALLEGRO_FONT* init_builtin_font(void)
{
	ALLEGRO_FONT* font = al_create_builtin_font();
	must_init(font, "font");

	return font;
}
*/
//?���? 추�??2


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
	init_sample();

#ifdef DEBUG_MODE
	DEBUG_clear_cat();
	DEBUG_clear_enemy();
	DEBUG_clear_magic();
	clear_explosion();
#else
	clear_cat();
	clear_enemy();
	clear_magic();
	clear_explosion();
#endif	
}

void textbox_init(TextBox* tb, float x, float y, float w, float h, int maxlen)
{
	tb->x = x; tb->y = y; tb->w = w; tb->h = h;
	tb->focused = false;
	tb->maxlen = (maxlen < (int)sizeof(tb->text) - 1) ? maxlen : (int)sizeof(tb->text) - 1;
	tb->len = 0;
	tb->text[0] = '\0';
}