#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES    3


#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6


#define BUFFER_W 320
#define BUFFER_H 240


static const int ALIEN_W[] = { 14, 13, 45 };
static const int ALIEN_H[] = { 9, 10, 27 };

#define ALIEN_BUG_W      ALIEN_W[0]
#define ALIEN_BUG_H      ALIEN_H[0]
#define ALIEN_ARROW_W    ALIEN_W[1]
#define ALIEN_ARROW_H    ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4



typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;

    ALLEGRO_BITMAP* ship;
    ALLEGRO_BITMAP* ship_shot[2];
    ALLEGRO_BITMAP* life;

    ALLEGRO_BITMAP* alien[3];
    ALLEGRO_BITMAP* alien_shot;

    ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

    ALLEGRO_BITMAP* powerup[4];
} SPRITES;

typedef struct SHIP
{
    int x, y;
    int shot_timer;
    int lives;
    int respawn_timer;
    int invincible_timer;
} SHIP;

void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();

void fx_init();
void fx_add(bool spark, int x, int y);
void fx_update();
void fx_draw();



ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h);
void sprites_init();
void sprites_deinit();

void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);



void shots_init();
bool shots_add(bool ship, bool straight, int x, int y);
void shots_update();
bool shots_collide(bool ship, int x, int y, int w, int h);
void shots_draw();