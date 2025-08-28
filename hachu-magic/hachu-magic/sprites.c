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

// internal �Լ� ����
static ALLEGRO_BITMAP* load_bitmap(const char* file_name);
static ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);

static ALLEGRO_BITMAP* load_bitmap(const char* file_name)
{
    ALLEGRO_BITMAP* temp = al_load_bitmap(file_name);
    must_init(temp, "load sprite");
    return temp;

}

/**
 * ��������Ʈ �̹����� �����Ʈ�� �����մϴ�.
 * �����Ʈ ������ ������ ��� ���α׷��� ����˴ϴ�.
 * @param sheet: ������ ���ϴ� ���� ��Ʈ
 * @param x: �߶󳻷��� ���� ���� �𼭸��� x ��ǥ
 * @param y: �߶󳻷��� ���� ��� �𼭸��� y ��ǥ
 * @param w: �߶󳻷��� ������ ���� ����
 * @param h: �߶󳻷��� ������ ���� ����
 * @return ALLEGRO_BITMAP*: �߶� bitmap �� �ּ�
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
    // TODO: Sprite�� �����ϱ�
    // �׽�Ʈ��: ���� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR enemy_color = al_map_rgb(0, 255, 0);  // ������

    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t temp = g_enemy_list[i];
        if(temp.is_spawned)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, enemy_color);
    }
}

void draw_magics(void)
{
    // TODO: Sprite�� �����ϱ�
    // �׽�Ʈ��: ������ �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR magic_color = al_map_rgb(0, 0, 255);  // ������

    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t temp = g_magic_list[i];
        if (temp.is_spawned)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, magic_color);
    }
}

void draw_fxs(void)
{

}