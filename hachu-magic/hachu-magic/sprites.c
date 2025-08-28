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

    g_sprites._cat_sheet = load_bitmap("assets/sprites/cat_sprite.png");
    g_sprites.cat[0] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 0, 0, CAT_WIDTH, CAT_HEIGHT);
    g_sprites.cat[1] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 1, 0, CAT_WIDTH, CAT_HEIGHT);
    g_sprites.cat[2] = sprite_grab(g_sprites._cat_sheet, CAT_WIDTH * 2, 0, CAT_WIDTH, CAT_HEIGHT);

    g_sprites._enemy_sheet = load_bitmap("assets/sprites/enemy_sprite.png");
    g_sprites.enemies[0][0] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[0] * 0, 0, ENEMY_WIDTH[0], ENEMY_HEIGHT[0]);
    g_sprites.enemies[0][1] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[0] * 1, 0, ENEMY_WIDTH[0], ENEMY_HEIGHT[0]);
    g_sprites.enemies[1][0] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[0] * 2 + ENEMY_WIDTH[1] * 0, 0, ENEMY_WIDTH[1], ENEMY_HEIGHT[1]);
    g_sprites.enemies[1][1] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[0] * 2 + ENEMY_WIDTH[1] * 1, 0, ENEMY_WIDTH[1], ENEMY_HEIGHT[1]);
    g_sprites.enemies[2][0] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[2] * 0, ENEMY_HEIGHT[1], ENEMY_WIDTH[2], ENEMY_HEIGHT[2]);
    g_sprites.enemies[2][1] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[2] * 1, ENEMY_HEIGHT[1], ENEMY_WIDTH[2], ENEMY_HEIGHT[2]);
    g_sprites.enemies[3][0] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[3] * 0, ENEMY_HEIGHT[1] + ENEMY_HEIGHT[2], ENEMY_WIDTH[3], ENEMY_HEIGHT[3]);
    g_sprites.enemies[3][1] = sprite_grab(g_sprites._enemy_sheet, ENEMY_WIDTH[3] * 1, ENEMY_HEIGHT[1] + ENEMY_HEIGHT[2], ENEMY_WIDTH[3], ENEMY_HEIGHT[3]);

    g_sprites._effect_sheet = load_bitmap("assets/sprites/effect_sprite.png");
    g_sprites.arrows[0] = sprite_grab(g_sprites._effect_sheet, 0, ARROW_HEIGHT * 0, ARROW_WIDTH, ARROW_HEIGHT);
    g_sprites.arrows[1] = sprite_grab(g_sprites._effect_sheet, 0, ARROW_HEIGHT * 1, ARROW_WIDTH, ARROW_HEIGHT);
    g_sprites.arrows[2] = sprite_grab(g_sprites._effect_sheet, 0, ARROW_HEIGHT * 2, ARROW_WIDTH, ARROW_HEIGHT);
    g_sprites.arrows[3] = sprite_grab(g_sprites._effect_sheet, 0, ARROW_HEIGHT * 3, ARROW_WIDTH, ARROW_HEIGHT);
    g_sprites.life = sprite_grab(g_sprites._effect_sheet, 0, ARROW_HEIGHT * 4, LIFE_WIDTH, LIFE_HEIGHT);
    g_sprites.magics[0][0] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 0, MAGIC_HEIGHT * 0, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[0][1] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 0, MAGIC_HEIGHT * 1, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[0][2] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 0, MAGIC_HEIGHT * 2, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[1][0] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 1, MAGIC_HEIGHT * 0, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[1][1] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 1, MAGIC_HEIGHT * 1, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[1][2] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 1, MAGIC_HEIGHT * 2, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[2][0] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 2, MAGIC_HEIGHT * 0, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[2][1] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 2, MAGIC_HEIGHT * 1, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[2][2] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 2, MAGIC_HEIGHT * 2, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[3][0] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 3, MAGIC_HEIGHT * 0, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[3][1] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 3, MAGIC_HEIGHT * 1, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.magics[3][2] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + MAGIC_WIDTH * 3, MAGIC_HEIGHT * 2, MAGIC_WIDTH, MAGIC_HEIGHT);
    g_sprites.explosion[0] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + EXPLOSION_WIDTH * 0, MAGIC_HEIGHT * 4, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
    g_sprites.explosion[1] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + EXPLOSION_WIDTH * 1, MAGIC_HEIGHT * 4, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
    g_sprites.explosion[2] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + EXPLOSION_WIDTH * 2, MAGIC_HEIGHT * 4, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
    g_sprites.explosion[3] = sprite_grab(g_sprites._effect_sheet, ARROW_WIDTH + EXPLOSION_WIDTH * 3, MAGIC_HEIGHT * 4, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);
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
    int bitmap_size_w;
    int bitmap_size_h;

    // �� 
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t enemy = g_enemy_list[i];
        if (enemy.is_spawned) {
            al_draw_bitmap(g_sprites.enemies[enemy.type][g_frames / 16 % ENEMY_FRAME_NUMBER], enemy.pos_x, enemy.pos_y,0);
        }
    }

    // �� �Ӹ��� ���� (���� ������ ���� ���� ���� �и�)
    for (int i = 0; i < ENEMY_MAX_NUMBER; ++i) {
        enemy_t enemy = g_enemy_list[i];
        if (enemy.is_spawned) {
            for (int ii = enemy.received_attack_count; ii < enemy.life; ++ii) {
                double arrow_pos_x = -0.5 * (enemy.life - enemy.received_attack_count) + ii;
                al_draw_bitmap(g_sprites.arrows[enemy.pattern[ii]], enemy.pos_x + arrow_pos_x * ARROW_WIDTH, enemy.pos_y - enemy.size_h / 2 - ARROW_HEIGHT /2 , 0);
            }
        }
    }
}

void draw_magics(void)
{
    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t temp = g_magic_list[i];
        if (temp.is_spawned)
            al_draw_bitmap(g_sprites.magics[temp.type][g_frames / 16 % MAGIC_FRAME_NUMBER], temp.pos_x, temp.pos_y, 0);
    }
}

void draw_fxs(void)
{

}