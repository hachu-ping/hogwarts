#define	_CRT_SECURE_NO_WARNINGS  // using scanf

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game_manager.h"
#include "enemy.h"
#include "fx.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "game_system.h"

#define MAX_RANK 5
#define MAX_NAME_LEN 20
#define RANK_FILE "ranking.txt"



// ---------------------------------------------------
int max_stage_number = 4;
int current_stage = 0;

int stage_wave_max_number[] = { 4,4,3,2 };
int current_wave = 0;

int stage_wave_create_enemy_number[] = { 6,5,4,2 };

rank_entry_t rankings[MAX_RANK];
int rank_count = 0;

game_state_t gm_state;
extern ALLEGRO_FONT* font_hud;

void init_game(game_state_t* gm_state) {
    gm_state->current_stage = 0;
    gm_state->current_wave = 0;
    gm_state->g_cat_life = 5;
    gm_state->game_clear = false;
    gm_state->gm_start_time = al_get_time();
    gm_state->gm_end_time = 0;

    gm_state->game_clear = false;
    gm_state->game_over = false;
    // printf("debug - init_game : start time %f\n", gm_state->gm_start_time);
}


bool is_game_over(game_state_t* gm_state) {
    if (gm_state->g_cat_life <= 0) {
        gm_state->game_over = true;
        // printf("debug - game over: life depleted\n");
        return true;  // 체력이 0 이하이면 종료
    }
    return false;
}

void is_game_clear(game_state_t* gm_state) {
    gm_state->gm_end_time = al_get_time();
    if (gm_state->g_cat_life > 0 && gm_state->current_stage >= MAX_STAGE_NUMBER) {
        printf("debug - is game clear - true \n");
        gm_state->game_clear = true;
        gm_state->time_taken = (float)(gm_state->gm_end_time - gm_state->gm_start_time);

    }
    else {
        gm_state->game_clear = false;
        gm_state->time_taken = -1.0f;
        printf("debug - is game clear - false\n");
    }
}

void load_rankings(void) {
    printf("debug - load_rankings\n");
    FILE* fp = fopen(RANK_FILE, "r");
    if (!fp) return;   // 해당 파일 존재하지 않음
    rank_count = 0;
    while (fscanf(fp, "%19s %f", rankings[rank_count].name, &rankings[rank_count].time) == 2) { // 이름 문자열 + 시간(float) 두 개가 모두 성공적으로 읽어진 경우 처리
        rank_count++;
        if (rank_count >= MAX_RANK) break;
    }
    fclose(fp);

}
/*
ranking.txt 형식

플레이어 이름 시간 읽어 배열에 저장

최대 10개까지 저장

파일 열고 닫기*/

void save_rankings(void) {
    printf("debug - save_rankings\n");
    FILE* fp = fopen(RANK_FILE, "w");
    if (!fp) return;
    for (int i = 0; i < rank_count; i++) {
        fprintf(fp, "%s %.2f\n", rankings[i].name, rankings[i].time);
    }
    fclose(fp);

}

int compare_scores(const void* a, const void* b) {
    const rank_entry_t* ra = a;
    const rank_entry_t* rb = b;

    if (ra->time < 0 && rb->time < 0) return 0;
    if (ra->time < 0) return 1;
    if (rb->time < 0) return -1;
    return (ra->time > rb->time) - (ra->time < rb->time);
}
/*
게임을 실패 (time == -1) 한 랭킹 은 자료 맨뒤로 보내 주기

게임을 완료한것만 짧은 시간 순서로 정렬
*/

void add_score(const char* name, float time) {
    // 자리 여유 있으면 그냥 추가
    if (rank_count < MAX_RANK) {
        strncpy(rankings[rank_count].name, name, MAX_NAME_LEN);
        rankings[rank_count].time = time;
        rank_count++;
    }
    else {
        // 가득 찬 경우: 실패 기록이 있는지 먼저 찾기
        int fail_index = -1;
        for (int i = 0; i < MAX_RANK; i++) {
            if (rankings[i].time < 0) {
                fail_index = i;
                break;
            }
        }

        if (fail_index != -1) {
            // 실패 기록이 있다면, 이것을 교체함
            strncpy(rankings[fail_index].name, name, MAX_NAME_LEN);
            rankings[fail_index].time = time;
        }
        else {
            // 모두 다 성공함, 주어진 점수 비교해 보기
            int worst_index = MAX_RANK - 1;
            float worst_time = rankings[worst_index].time;

            if (time < 0) return; // 게임을 실패한 경우
            if (time >= worst_time) return; // 더 느린 점수이면 무시

            // 교체함
            strncpy(rankings[worst_index].name, name, MAX_NAME_LEN);
            rankings[worst_index].time = time;
        }
    }

    // 정렬
    qsort(rankings, rank_count, sizeof(rank_entry_t), compare_scores);
}


// 화면에 랭킹 출력하는 함수

void print_rankings_screen(ALLEGRO_FONT* font, game_state_t* gm_state) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    if (gm_state->game_clear) {
        al_draw_text(font, al_map_rgb(0, 255, 0), 650, 160, 0, "Game Clear!");
    }
    else if (gm_state->game_over) {
        al_draw_text(font, al_map_rgb(255, 0, 0), 650, 160, 0, "Game Over!");
    }

    al_draw_textf(font, al_map_rgb(255, 255, 255), 600, 230, 0, "=== RANKINGS ===");

    for (int i = 0; i < rank_count; i++) {
        if (rankings[i].time < 0) {
            al_draw_textf(font, al_map_rgb(255, 255, 255), 610, 300 + i * 30, 0,
                "%2d. %-10s  --초", i + 1, rankings[i].name);
        }
        else {
            al_draw_textf(font, al_map_rgb(255, 255, 255), 610, 300 + i * 30, 0,
                "%2d. %-10s  %.2f초", i + 1, rankings[i].name, rankings[i].time);
        }
    }

    al_flip_display();
}





int g_frames = 0;

char g_player_name[64] = { 0 };


//함수 별 초기화
void clear_data(void)
{
    current_stage = 0;
    current_wave = 0;

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

void play_game(void)
{
    clear_data();

    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();

    // 현 디스플레이 소스를 등록해야 DISPLAY_CLOSE를 받습니다.
    ALLEGRO_DISPLAY* disp = al_get_current_display();
    al_register_event_source(queue, al_get_display_event_source(disp));

    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    init_game(&gm_state);

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
            // === 업데이트 ===
        
            update_cat();
            spawn_enemy();
            move_magic();
            move_enemy();
            handle_magic_collision();
            handle_enemy_collision();
            update_explosion();

            redraw = true;       // 매 틱마다 다 시 그리기
            break;
        }

        // === 그리기 ===
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            refresh_screen();
            draw_hud(font_hud, &gm_state);
        }
    }

    if (gm_state.game_clear) {
        load_rankings();
        add_score("test", gm_state.time_taken);
        save_rankings();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

extern void play_game(void);

void start_play_stage(ALLEGRO_EVENT_QUEUE* main_queue)
{
    // 원래 씬 기록(나중에 돌아 올 때용)
    Scene prev = g_scene_screne;

    g_scene_screne = SCENE_PLAY;

    if (main_queue) al_pause_event_queue(main_queue, true);
    play_game();
    if (main_queue) {
        al_pause_event_queue(main_queue, false);
        al_flush_event_queue(main_queue);
    }

    g_scene_screne = SCENE_TITLE;
}
int life = 5;

void apply_damage(int damage)
{
    gm_state.g_cat_life -= damage;

    DEBUG_PRINT("충돌 발생 life -> %d %d\n", damage, gm_state.g_cat_life);

    is_game_over(&gm_state);

    if (gm_state.g_cat_life <= 0) {
        // TODO: 게임오버 처리하기
        is_game_over(&gm_state);
        DEBUG_PRINT("게임 종료\n");
    }
}

void draw_hud(ALLEGRO_FONT* font, game_state_t* gm_state) {
    double now = al_get_time();                  // 현재 시간 (초 단위)
    double elapsed = now - gm_state->gm_start_time; // 게임 시작 후 경과 시간

    al_draw_textf(font_hud, al_map_rgb(255, 255, 255), 700, 50, 20,
        "Stage: %d   Life: %d   Time: %.1f s",
        gm_state->current_stage + 1, gm_state->g_cat_life, elapsed);
    
    al_flip_display();
}
void draw_stage_announce(ALLEGRO_FONT* font, game_state_t* gm_state) {
    al_clear_to_color(al_map_rgb(0, 0, 0));  // 화면 잠깐 비우기
    if (gm_state->current_stage < 4)
        al_draw_textf(font_stage, al_map_rgb(255, 200, 200), 700, 400, ALLEGRO_ALIGN_CENTER,
            "Stage %d", gm_state->current_stage + 1);
    else
        al_draw_text(font_stage, al_map_rgb(255, 100, 100), 700, 400, ALLEGRO_ALIGN_CENTER,
            "Final Stage!");
    al_flip_display();
    al_rest(1.0); // 2초 동안 표시
}
