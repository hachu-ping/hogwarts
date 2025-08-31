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
#include "screen.h"
#include "scene_manager.h"

extern game_state_t gm_state;

void refresh_game_screen(void)
{
    refresh_background();
    refresh_enemies();
    refresh_cat();
    refresh_magics();
    refresh_fxs();

    al_flip_display();
}

void refresh_background(void)
{
    int current_stage = gm_state.current_stage;
    draw_background(current_stage);
}

void refresh_cat(void)
{
    const cat_t* cat = get_cat();
    draw_cat(cat->pos_x, cat->pos_y, cat->size_w, cat->size_h);
}

void refresh_enemies(void)
{
    const enemy_t* enemy_list = get_enemy_list();

    // 적 
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* enemy = enemy_list + i;
        if (enemy->is_spawned) {
            draw_enemy(enemy->pos_x, enemy->pos_y, enemy->size_w, enemy->size_h, enemy->type);
        }
    }

    // 적 머리 위 화살표 (겹치지 않도록 두 번째 반복문 실행) 
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* enemy = enemy_list + i;
        if (enemy->is_spawned) {
            draw_enemy_arrow(enemy->pos_x, enemy->pos_y, enemy->size_w, enemy->size_h, enemy->type, enemy->pattern, enemy->life, enemy->received_attack_count);
        }
    }
}

void refresh_magics(void)
{
    const magic_t* magic_list = get_magic_list();

    for (int i = 0; i < MAGIC_MAX_NUMBER; i++) {
        magic_t* magic = magic_list + i;
        if (magic->is_spawned)
        {

        }
    }
}

void refresh_fxs(void)
{
    const explosion_t* explosion_list = get_magic_list();

    for (int i = 0; i < EXPLOSION_MAX_NUMBER; i++) {
        explosion_t* explosion = explosion_list + i;
        if (explosion->is_spawned)
        {
            draw_fxs(explosion->pos_x, explosion->pos_y, explosion->current_frame);
        }
    }
}

void refresh_scene(void)
{
    const scene_manager_t* scene_manager = get_scene_manager();

    switch (scene_manager->current_scene) {
    case SCENE_TITLE:
        draw_title_screen();
        break;
    case SCENE_PLAY:

    case SCENE_RANK:

    }

    al_flip_display();
}

void draw_title_screen(void)
{
    draw_background(BACKGROUND_TYPE_START);

    draw_textbox(&g_name_box);
    draw_text(700, 250, "CAT vs MICE");

    draw_button(&start_button, al_map_rgb(60, 120, 250), al_map_rgb(255, 255, 255), 2.0f);
    draw_button(&rank_button, al_map_rgb(80, 180, 120), al_map_rgb(255, 255, 255), 2.0f);

    draw_text(700, 560, "Enter: start   R: rank   ESC: end");
}