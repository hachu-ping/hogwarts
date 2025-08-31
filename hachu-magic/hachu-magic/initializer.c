

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
#include "game_manager.h"
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

	// font addon initialize
	must_init(al_init_font_addon(), "font addon init");
	must_init(al_init_ttf_addon(), "ttf font addon init");

	// audios
	must_init(al_init_acodec_addon(), "audio codecs");
	must_init(al_reserve_samples(32), "reserve samples");  //샘플의 키홀드값
}

void install_driver(void)
{
	must_init(al_install_keyboard(), "keyboard");
	must_init(al_install_mouse(), "mouse");
	must_init(al_install_audio(), "audio");
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
	memset(g_key, 0, sizeof(g_key));

	load_sprites();
	load_audios();
	load_fonts();

	load_rankings();
	textbox_init(get_text_box(), start_button.x, start_button.y, start_button.w, start_button.h, MAX_NAME_LEN);
}

void textbox_init(text_box_t* tb, float x, float y, float w, float h, int maxlen)
{
	tb->x = x; tb->y = y; tb->w = w; tb->h = h;
	tb->focused = false;
	tb->maxlen = (maxlen < (int)sizeof(tb->text) - 1) ? maxlen : (int)sizeof(tb->text) - 1;
	tb->len = 0;
	tb->text[0] = '\0';
}