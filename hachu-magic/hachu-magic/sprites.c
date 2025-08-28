
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
extern enemy_t g_enemies[ENEMY_MAX_NUMBER];
extern magic_t g_magics[MAGIC_MAX_NUMBER];

void init_sprites(void)
{
    // load placeholder image
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background-image");
}

void refresh_screen(void)
{
    draw_background();
    draw_enemies();
    draw_cat();
    draw_magics();
    draw_fx();

    al_flip_display();

}

void draw_background(void)
{
    //al_draw_bitmap(background, 0, 0, 0);
    //al_draw_scaled_bitmap(background, 0, 0, 640, 437, 0, 0, 1400, 800, 0); // �̹��� ũ�� ������� ���߱�
}

void draw_cat(void)
{   
    // TODO: Sprite�� �����ϱ�
    // �׽�Ʈ��: ����̸� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // ������

    al_draw_filled_rectangle(g_cat.pos_x, g_cat.pos_y, g_cat.pos_x + g_cat.size_w, g_cat.pos_y + g_cat.size_h, cat_color);
}

void draw_enemies(void)
{
    // TODO: Sprite�� �����ϱ�
    // �׽�Ʈ��: ���� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR enemy_color = al_map_rgb(0, 255, 0);  // ������

    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t temp = g_enemies[i];
        if(temp.used)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, enemy_color);
    }
}

void draw_magics(void)
{
    // TODO: Sprite�� �����ϱ�
    // �׽�Ʈ��: ������ �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR magic_color = al_map_rgb(0, 0, 255);  // ������

    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t temp = g_magics[i];
        if (temp.used)
            al_draw_filled_rectangle(temp.pos_x, temp.pos_y, temp.pos_x + temp.size_w, temp.pos_y + temp.size_h, magic_color);
    }
}

void draw_fx(void)
{

}