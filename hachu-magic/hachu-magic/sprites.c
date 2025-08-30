#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"

extern cat_t g_cat;
extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];
extern magic_t g_magic_list[MAGIC_MAX_NUMBER];

extern int g_frames;

SPRITES g_sprites;

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

    g_sprites._cat_sheet = load_bitmap("assets/sprites/cat_sprite.png");
    g_sprites.cat[0] = sprite_grab(g_sprites._cat_sheet, SPRITE_CAT_WIDTH * 0, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);
    g_sprites.cat[1] = sprite_grab(g_sprites._cat_sheet, SPRITE_CAT_WIDTH * 1, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);
    g_sprites.cat[2] = sprite_grab(g_sprites._cat_sheet, SPRITE_CAT_WIDTH * 2, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);

    g_sprites._enemy_sheet = load_bitmap("assets/sprites/enemy_sprite.png");
    g_sprites.enemies[0][0] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 0, 0, SPRITE_ENEMY_WIDTH[0], SPRITE_ENEMY_HEIGHT[0]);
    g_sprites.enemies[0][1] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 1, 0, SPRITE_ENEMY_WIDTH[0], SPRITE_ENEMY_HEIGHT[0]);
    g_sprites.enemies[1][0] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 2 + SPRITE_ENEMY_WIDTH[1] * 0, 0, SPRITE_ENEMY_WIDTH[1], SPRITE_ENEMY_HEIGHT[1]);
    g_sprites.enemies[1][1] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 2 + SPRITE_ENEMY_WIDTH[1] * 1, 0, SPRITE_ENEMY_WIDTH[1], SPRITE_ENEMY_HEIGHT[1]);
    g_sprites.enemies[2][0] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[2] * 0, SPRITE_ENEMY_HEIGHT[1], SPRITE_ENEMY_WIDTH[2], SPRITE_ENEMY_HEIGHT[2]);
    g_sprites.enemies[2][1] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[2] * 1, SPRITE_ENEMY_HEIGHT[1], SPRITE_ENEMY_WIDTH[2], SPRITE_ENEMY_HEIGHT[2]);
    g_sprites.enemies[3][0] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[3] * 0, SPRITE_ENEMY_HEIGHT[1] + SPRITE_ENEMY_HEIGHT[2], SPRITE_ENEMY_WIDTH[3], SPRITE_ENEMY_HEIGHT[3]);
    g_sprites.enemies[3][1] = sprite_grab(g_sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[3] * 1, SPRITE_ENEMY_HEIGHT[1] + SPRITE_ENEMY_HEIGHT[2], SPRITE_ENEMY_WIDTH[3], SPRITE_ENEMY_HEIGHT[3]);

    g_sprites._effect_sheet = load_bitmap("assets/sprites/effect_sprite.png");
    g_sprites.arrows[1] = sprite_grab(g_sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 0, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    g_sprites.arrows[2] = sprite_grab(g_sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 1, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    g_sprites.arrows[3] = sprite_grab(g_sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 2, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    g_sprites.arrows[4] = sprite_grab(g_sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 3, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    g_sprites.life = sprite_grab(g_sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 4, SPRITE_LIFE_WIDTH, SPRITE_LIFE_HEIGHT);
    g_sprites.magics[1][0] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[1][1] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[1][2] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[2][0] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[2][1] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[2][2] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[3][0] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[3][1] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[3][2] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[4][0] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[4][1] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.magics[4][2] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    g_sprites.explosion[0] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    g_sprites.explosion[1] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    g_sprites.explosion[2] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    g_sprites.explosion[3] = sprite_grab(g_sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
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
    int x_offset = (g_cat.size_w - SPRITE_CAT_WIDTH) * 0.5;
    int y_offset = (g_cat.size_h - SPRITE_CAT_HEIGHT) * 0.5;

    al_draw_bitmap(
        g_sprites.cat[g_frames / 12 % SPRITE_CAT_FRAME_NUMBER],
        g_cat.pos_x + x_offset,
        g_cat.pos_y + y_offset,
        0
    );

#ifdef DEBUG_MODE
    // 충돌 영역 표시
    al_draw_rectangle(g_cat.pos_x, g_cat.pos_y, g_cat.pos_x + g_cat.size_w, g_cat.pos_y + g_cat.size_h, al_map_rgb(0, 255, 0), 3);
#endif
}

void draw_enemies(void)
{
    int bitmap_size_w;
    int bitmap_size_h;

    // 적 
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* enemy = g_enemy_list + i;
        if (enemy->is_spawned) {
            int x_offset = (enemy->size_w - SPRITE_ENEMY_WIDTH[enemy->type]) * 0.5;
            int y_offset = (enemy->size_h - SPRITE_ENEMY_HEIGHT[enemy->type]) * 0.5;

            al_draw_bitmap(
                g_sprites.enemies[enemy->type][g_frames / 16 % SPRITE_ENEMY_FRAME_NUMBER],
                enemy->pos_x + x_offset,
                enemy->pos_y + y_offset,
                0
            );
#ifdef DEBUG_MODE
            // 충돌 영역 표시
            al_draw_rectangle(enemy->pos_x, enemy->pos_y, enemy->pos_x + enemy->size_w, enemy->pos_y + enemy->size_h, al_map_rgb(255, 0, 0), 3);
#endif
        }
    }

    // 적 머리위 패턴 (패턴 가려짐 방지 위해 로직 분리)
    for (int i = 0; i < ENEMY_MAX_NUMBER; ++i) {
        enemy_t* enemy = g_enemy_list + i;
        if (enemy->is_spawned) {
            for (int ii = enemy->received_attack_count; ii < enemy->life; ++ii) {
                double arrow_pos_x_offset = 0.5 * enemy->size_w + (-0.5 * (enemy->life - enemy->received_attack_count)) * SPRITE_ARROW_WIDTH + (ii - enemy->received_attack_count) * SPRITE_ARROW_WIDTH;
                double arrow_pos_y_offset = (enemy->size_h - SPRITE_ENEMY_HEIGHT[enemy->type]) * 0.5 - (SPRITE_ARROW_HEIGHT * 0.8);
                al_draw_bitmap(
                    g_sprites.arrows[enemy->pattern[ii]],
                    enemy->pos_x + arrow_pos_x_offset,
                    enemy->pos_y + arrow_pos_y_offset,
                    0
                );
            }
        }
    }
}

void draw_magics(void)
{
    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t* temp = g_magic_list + i;
        if (temp->is_spawned)
        {
            al_draw_bitmap(
                g_sprites.magics[temp->type][g_frames / 16 % SPRITE_MAGIC_FRAME_NUMBER],
                temp->pos_x,
                temp->pos_y,
                0
            );
            
#ifdef DEBUG_MODE
            // 충돌 영역 표시
            al_draw_rectangle(temp->pos_x, temp->pos_y, temp->pos_x + temp->size_w, temp->pos_y + temp->size_h, al_map_rgb(0, 0, 255), 3);
#endif
        }
    }
}

void draw_fxs(void)
{

    for (int i = 0; i < EXPLOSION_MAX_NUMBER; i++) {
        explosion_t* temp = g_explosion_list + i;
        if (temp->is_spawned)
        {
            al_draw_bitmap(
                g_sprites.explosion[temp->current_frame / 4],
                temp->pos_x,
                temp->pos_y,
                0
            );
        }
    }
}