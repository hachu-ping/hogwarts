#define	_CRT_SECURE_NO_WARNINGS  // using scanf

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "audio.h"
#include "debug.h"
#include "game_manager.h"
#include "enemy.h"
#include "fx.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "game_system.h"


int max_stage_number = 4;
int stage_wave_max_number[] = { 4,4,3,2 };

int stage_wave_create_enemy_number[] = { 6,5,4,2 };

int g_frames = 0;
static game_state_t gm_state;

inline const game_state_t* get_game_state(void)
{
    return &gm_state;
}


void play_game(void)
{

    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();

    // 현 디스플레이 소스를 등록해야 DISPLAY_CLOSE를 받습니다.
    ALLEGRO_DISPLAY* disp = al_get_current_display();
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    init_game();

    draw_stage_announce();

    bool redraw = true;   // 첫 프레임 무조건 그리기

    while (!gm_state.game_over && !gm_state.game_clear) {
        g_frames++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        keyboard_update(&ev);

        switch (ev.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            gm_state.game_over = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                gm_state.game_over = true;
            }
            break;

        case ALLEGRO_EVENT_TIMER:
            update_cat();
            spawn_enemy();
            move_magic();
            move_enemy();
            handle_magic_collision();
            handle_enemy_collision();
            update_explosion();

            redraw = true;       // 매 틱마다 다시 그리기
            break;
        }

        // === 그리기 ===
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            refresh_game_screen();
            al_flip_display();
        }
    }

    if (gm_state.game_clear) {
        load_rankings();
        add_score(gm_state.player_name, gm_state.time_taken);  // 수정 필요
        save_rankings();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}


void init_game() {
    gm_state.current_stage = 0;
    gm_state.current_wave = 0;
    gm_state.g_cat_life = 5;
    gm_state.gm_start_time = al_get_time();
    gm_state.gm_end_time = 0;

    gm_state.game_clear = false;
    gm_state.game_over = false;

    clear_data();
}


bool is_game_over() {
    if (gm_state.g_cat_life <= 0) {
        gm_state.game_over = true;

        return true;  // 체력이 0 이하이면 종료
    }
    return false;
}

void is_game_clear() {
    gm_state.gm_end_time = al_get_time();
    if (get_game_state()->g_cat_life > 0 && gm_state.current_stage >= MAX_STAGE_NUMBER) {
        DEBUG_PRINT("debug - is game clear - true \n");
        gm_state.game_clear = true;
        gm_state.time_taken = (double)(gm_state.gm_end_time - gm_state.gm_start_time);

    }
    else {
        gm_state.game_clear = false;
        gm_state.time_taken = -1.0f;
        DEBUG_PRINT("debug - is game clear - false\n");
    }
}

void move_to_next_wave(void)
{
    gm_state.current_wave += 1;
}


void move_to_next_stage(void)
{
    gm_state.current_wave = 0;
    gm_state.current_stage += 1;

    draw_stage_announce();
}


void prepare_game_start(void) 
{
    update_player_name(get_name_box()->text, get_name_box()->len);

    textbox_clear(get_name_box());
}

//함수 별 초기화
void clear_data(void)
{

#if __DEBUG_MODE__
    DEBUG_clear_cat();
    DEBUG_clear_enemy();
    DEBUG_clear_magic();
#else
    clear_cat();
    clear_enemy();
    clear_magic();
#endif	
}


void start_play_stage(ALLEGRO_EVENT_QUEUE* main_queue)
{
    if (main_queue) al_pause_event_queue(main_queue, true);
    play_game();
    if (main_queue) {
        al_pause_event_queue(main_queue, false);
        al_flush_event_queue(main_queue);
    }
}

void apply_damage(int damage)
{
    gm_state.g_cat_life -= damage;

    play_sound(GAME_SOUND_CAT_DAMAGED);
    DEBUG_PRINT("충돌 발생 life -> %d %d\n", damage, gm_state.g_cat_life);

    is_game_over();
}

void update_player_name(char* name, int size)
{
    if (size > 0) { 
        STRCPY_SAFE(gm_state.player_name, name); 
        gm_state.player_name[size] = '\0';
    } else { 
        STRCPY_SAFE(gm_state.player_name, "guest"); 
        gm_state.player_name[5] = '\0';

    }

}