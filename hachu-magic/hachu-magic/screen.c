#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
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


void refresh_game_screen(void)
{
    refresh_background();
    refresh_enemies();
    refresh_cat();
    refresh_magics();
    refresh_fxs();
    refresh_hud();


    al_flip_display();
}

void refresh_background(void)
{
    int current_stage = get_game_state()->current_stage;
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
            draw_magic(magic->pos_x, magic->pos_y, magic->size_w, magic->size_h, magic->type);
        }
    }
}

void refresh_fxs(void)
{
    const explosion_t* explosion_list = get_explosion_list();

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
        draw_ranking_screen();
        break;
    }

    al_flip_display();
}

void draw_title_screen(void)
{
    draw_background(BACKGROUND_TYPE_START);

    draw_text(700, 250, "CAT vs MICE");

    draw_button(&start_button, al_map_rgb(60, 120, 250), al_map_rgb(255, 255, 255), 2.0f);
    draw_button(&rank_button, al_map_rgb(80, 180, 120), al_map_rgb(255, 255, 255), 2.0f);

    draw_text(700, 560, "Enter: start   R: rank   ESC: end");
    draw_textbox(get_name_box());
}


void refresh_hud(void)
{
    double now = al_get_time();                  // 현재 시간 (초 단위)
    double elapsed = now - get_game_state()->gm_start_time; // 게임 시작 후 경과 시간

    char hud_buffer[256];
    snprintf(hud_buffer, sizeof(hud_buffer),
        "Stage: %d   Life: %d   Time: %.1f s",
        get_game_state()->current_stage + 1, get_game_state()->g_cat_life, elapsed);

    draw_hud_text(760, 30, hud_buffer);
}

void draw_stage_announce(void) 
{
    al_clear_to_color(al_map_rgb(0, 0, 0));  // 화면 잠깐 비우기

    char hud_buffer[256];

    if (get_game_state()->current_stage <= MAX_STAGE_NUMBER - 2) {
        snprintf(hud_buffer, sizeof(hud_buffer), "Stage %d", get_game_state()->current_stage + 1);
    } else if (get_game_state()->current_stage == MAX_STAGE_NUMBER - 1) {
        memcpy(hud_buffer, "Final Stage!", 13);
    }
    else {
        memcpy(hud_buffer, "CLEAR!", 7);
    }
    
    draw_stage_text(700, 350, hud_buffer);
    al_flip_display();

    al_rest(1); // 1초 동안 표시
}

void draw_ranking_screen(void)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (get_game_state()->game_clear) {
        draw_text_color(740, 180, "Game Clear!", al_map_rgb(0, 255, 0));
    }
    else if (get_game_state()->game_over) {
        draw_text_color(740, 180, "Game Over!", al_map_rgb(255, 0, 0));
    }

    draw_text(730, 230,  "======== RANKINGS ========");

    char hud_buffer[256];
    for (int i = 0; i < get_rank_count(); i++) {
        if ((get_rankings()[i]).time < 0) {
            snprintf(hud_buffer, sizeof(hud_buffer), "%2d. %-10s    --  s", i + 1, (get_rankings()[i]).name);
            draw_text(720, 300 + i * 30, hud_buffer);
        }
        else {
            snprintf(hud_buffer, sizeof(hud_buffer), "%2d. %-10s  %.2f s", i + 1, (get_rankings()[i]).name, (get_rankings()[i]).time);
            draw_text(720, 300 + i * 30, hud_buffer);
        }
    }
}