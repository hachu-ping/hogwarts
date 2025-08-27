#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "sprites.h"
#include "utils.h"

SPRITES g_sprites;

extern int g_frames;
extern cat_t g_cat;

// internal 함수 선언
static ALLEGRO_BITMAP* load_bitmap(const char* file_name);
static ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);

static ALLEGRO_BITMAP* load_bitmap(const char* file_name)
{
    ALLEGRO_BITMAP* temp = al_load_bitmap(file_name);
    must_init(temp, "load sprite");
    return temp;

}

/**
 * 스프라이트 이미지를 서브비트로 가공합니다.
 * 서브비트 가공에 실패할 경우 프로그램이 종료됩니다.
 * @param sheet: 가공을 원하는 원본 시트
 * @param x: 잘라내려는 구역 왼쪽 모서리의 x 좌표
 * @param y: 잘라내려는 구역 상단 모서리의 y 좌표
 * @param w: 잘라내려는 구역의 가로 길이
 * @param h: 잘라내려는 구역의 가로 길이
 * @return ALLEGRO_BITMAP*: 잘라낸 bitmap 의 주소
 */
static ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}


void init_sprites(void)
{
    g_sprites.background[0] = load_bitmap("placeholder.jpeg");

    g_sprites._cat_sheet = load_bitmap("assets/cat_sprite.png");
    g_sprites.cat[0] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 0, 0, CAT_WIDTH, CAT_HEIGHT);
    g_sprites.cat[1] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 1, 0, CAT_WIDTH, CAT_HEIGHT);
    g_sprites.cat[2] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 2, 0, CAT_WIDTH, CAT_HEIGHT);

}

void draw_background(void)
{
    al_draw_scaled_bitmap(g_sprites.background[0], 0, 0, 640, 437, 0, 0, 1400, 800, 0);
}

void draw_cat(void)
{
    al_draw_bitmap(g_sprites.cat[g_frames / 12 % CAT_FRAME_NUMBER], g_cat.pos_x, g_cat.pos_y, 0);
}

void draw_magics(void)
{

}

void draw_enemies(void)
{

}

/*

#define SHIP_W 12
#define SHIP_H 13

#define SHIP_SHOT_W 2
#define SHIP_SHOT_H 9

#define LIFE_W 6
#define LIFE_H 6

const int ALIEN_W[] = { 14, 13, 45 };
const int ALIEN_H[] = { 9, 10, 27 };

#define ALIEN_BUG_W      ALIEN_W[0]
#define ALIEN_BUG_H      ALIEN_H[0]
#define ALIEN_ARROW_W    ALIEN_W[1]
#define ALIEN_ARROW_H    ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

#define ALIEN_SHOT_W 4
#define ALIEN_SHOT_H 4

#define EXPLOSION_FRAMES 4
#define SPARKS_FRAMES    3


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
SPRITES sprites;



void sprites_init()
{
    sprites._sheet = al_load_bitmap("spritesheet.png");
    must_init(sprites._sheet, "spritesheet");

    sprites.ship = sprite_grab(0, 0, SHIP_W, SHIP_H);

    sprites.ship_shot[0] = sprite_grab(13, 0, SHIP_SHOT_W, SHIP_SHOT_H);
    sprites.ship_shot[1] = sprite_grab(16, 0, SHIP_SHOT_W, SHIP_SHOT_H);

    sprites.life = sprite_grab(0, 14, LIFE_W, LIFE_H);

    sprites.alien[0] = sprite_grab(19, 0, ALIEN_BUG_W, ALIEN_BUG_H);
    sprites.alien[1] = sprite_grab(19, 10, ALIEN_ARROW_W, ALIEN_ARROW_H);
    sprites.alien[2] = sprite_grab(0, 21, ALIEN_THICCBOI_W, ALIEN_THICCBOI_H);

    sprites.alien_shot = sprite_grab(13, 10, ALIEN_SHOT_W, ALIEN_SHOT_H);

    sprites.explosion[0] = sprite_grab(33, 10, 9, 9);
    sprites.explosion[1] = sprite_grab(43, 9, 11, 11);
    sprites.explosion[2] = sprite_grab(46, 21, 17, 18);
    sprites.explosion[3] = sprite_grab(46, 40, 17, 17);

    sprites.sparks[0] = sprite_grab(34, 0, 10, 8);
    sprites.sparks[1] = sprite_grab(45, 0, 7, 8);
    sprites.sparks[2] = sprite_grab(54, 0, 9, 8);

    sprites.powerup[0] = sprite_grab(0, 49, 9, 12);
    sprites.powerup[1] = sprite_grab(10, 49, 9, 12);
    sprites.powerup[2] = sprite_grab(20, 49, 9, 12);
    sprites.powerup[3] = sprite_grab(30, 49, 9, 12);
}

void sprites_deinit()
{
    al_destroy_bitmap(sprites.ship);

    al_destroy_bitmap(sprites.ship_shot[0]);
    al_destroy_bitmap(sprites.ship_shot[1]);

    al_destroy_bitmap(sprites.life);

    al_destroy_bitmap(sprites.alien[0]);
    al_destroy_bitmap(sprites.alien[1]);
    al_destroy_bitmap(sprites.alien[2]);

    al_destroy_bitmap(sprites.alien_shot);

    al_destroy_bitmap(sprites.explosion[0]);
    al_destroy_bitmap(sprites.explosion[1]);
    al_destroy_bitmap(sprites.explosion[2]);
    al_destroy_bitmap(sprites.explosion[3]);

    al_destroy_bitmap(sprites.sparks[0]);
    al_destroy_bitmap(sprites.sparks[1]);
    al_destroy_bitmap(sprites.sparks[2]);

    al_destroy_bitmap(sprites.powerup[0]);
    al_destroy_bitmap(sprites.powerup[1]);
    al_destroy_bitmap(sprites.powerup[2]);
    al_destroy_bitmap(sprites.powerup[3]);

    al_destroy_bitmap(sprites._sheet);
}
*/