#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "cat.h"
#include "enemy.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"



extern cat_t g_cat;
extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];
extern magic_t g_magic_list[MAGIC_MAX_NUMBER];

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

void refresh_screen(void)
{
    draw_background();
    draw_enemies();
    draw_cat();
    draw_magics();
    draw_fxs();

    al_flip_display();
}


void draw_background(void)
{
    al_draw_scaled_bitmap(g_sprites.background[0], 0, 0, 640, 437, 0, 0, 1400, 800, 0);
}

void draw_cat(void)
{
    al_draw_bitmap(g_sprites.cat[g_frames / 12 % CAT_FRAME_NUMBER], g_cat.pos_x, g_cat.pos_y, 0);
}

void draw_enemies(void)
{
    // TODO: Sprite로 변경하기
    // 테스트용: 적을 사각형으로 표시 (50x50 크기)
    ALLEGRO_COLOR enemy_color = al_map_rgb(0, 255, 0);  // 빨간색

    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t temp = g_enemy_list[i];
        if(temp.is_spawned)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, enemy_color);
    }
}

void draw_magics(void)
{
    // TODO: Sprite로 변경하기
    // 테스트용: 마법을 사각형으로 표시 (50x50 크기)
    ALLEGRO_COLOR magic_color = al_map_rgb(0, 0, 255);  // 빨간색

    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t temp = g_magic_list[i];
        if (temp.is_spawned)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, magic_color);
    }
}

void draw_fxs(void)
{

}