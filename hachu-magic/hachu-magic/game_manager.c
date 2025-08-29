#define	_CRT_SECURE_NO_WARNINGS  // using scanf
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "game_manager.h"
#include <stdbool.h>

#define MAX_RANK 5
#define MAX_NAME_LEN 20
#define RANK_FILE "ranking.txt"


// ---------------------------------------------------
int max_stage_number = 2;
int current_stage = 0;

int stage_wave_max_number[] = { 2, 3, 4 };
int current_wave = 0;

int stage_wave_spawn_enemy_number[] = { 5, 6, 7 };
// ----------------------------------------------------

RankEntry rankings[MAX_RANK];
int rank_count = 0;
GameState gm_state;

void init_game(GameState* gm_state) {
    gm_state->current_stage = 0;
    gm_state->g_cat_life = 5;
    gm_state->game_clear = false;
    gm_state->gm_start_time = al_get_time();
    gm_state->gm_end_time = 0;
    // printf("debug - init_game : start time %f\n", gm_state->gm_start_time);
}


void is_game_over(GameState* gm_state) {
    if (gm_state->g_cat_life <= 0) {
        gm_state->game_over = true;
        // printf("debug - game over: life depleted\n");
        return true;  // 고양이 목숨이 0이면 오버
    }
    return false;
}

void is_game_clear(GameState* gm_state) {
    gm_state->gm_end_time = al_get_time();
    if (gm_state->g_cat_life > 0 && gm_state->current_stage >= 2) {
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
    if (!fp) return;   // 해당 파일 없으면 무시
    rank_count = 0;
    while (fscanf(fp, "%19s %f", rankings[rank_count].name, &rankings[rank_count].time) == 2) { // 이름 문자열 + 기록(float) 두 개를 모두 성공적으로 읽었을 때만 처리
        rank_count++;
        if (rank_count >= MAX_RANK) break;
    }
    fclose(fp);

}
/*
ranking.txt 열기

줄마다 이름 시간 읽어서 배열에 저장

최대 10개까지 저장

파일 닫고 끝*/

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
    const RankEntry* ra = a;
    const RankEntry* rb = b;

    if (ra->time < 0 && rb->time < 0) return 0;
    if (ra->time < 0) return 1;
    if (rb->time < 0) return -1;
    return (ra->time > rb->time) - (ra->time < rb->time);
}
/*
실패한 기록 (time == -1) 은 랭킹 맨 뒤로 가게 함

성공한 기록끼리는 빠른 시간 순서로 정렬
*/

void add_score(const char* name, float time) {
    // 자리 남아 있으면 그냥 추가
    if (rank_count < MAX_RANK) {
        strncpy(rankings[rank_count].name, name, MAX_NAME_LEN);
        rankings[rank_count].time = time;
        rank_count++;
    }
    else {
        // 꽉 찬 경우: 실패 기록이 있는지 먼저 찾기
        int fail_index = -1;
        for (int i = 0; i < MAX_RANK; i++) {
            if (rankings[i].time < 0) {
                fail_index = i;
                break;
            }
        }

        if (fail_index != -1) {
            // 실패 기록이 있다면, 무조건 덮어쓰기
            strncpy(rankings[fail_index].name, name, MAX_NAME_LEN);
            rankings[fail_index].time = time;
        }
        else {
            // 실패 기록 없으면, 최악의 성공 기록과 비교
            int worst_index = MAX_RANK - 1;
            float worst_time = rankings[worst_index].time;

            if (time < 0) return; // 실패한 기록은 무시
            if (time >= worst_time) return; // 더 느린 기록이면 무시

            // 덮어쓰기
            strncpy(rankings[worst_index].name, name, MAX_NAME_LEN);
            rankings[worst_index].time = time;
        }
    }

    // 정렬
    qsort(rankings, rank_count, sizeof(RankEntry), compare_scores);
}


// 화면에 랭킹 출력하는 함수

void print_rankings_screen(ALLEGRO_FONT* font, GameState* gm_state) {
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




