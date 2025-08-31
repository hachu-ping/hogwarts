#define	_CRT_SECURE_NO_WARNINGS  // using scanf

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "game_manager.h"

#define MAX_RANK 5
#define MAX_NAME_LEN 20
#define RANK_FILE "ranking.txt"


// ---------------------------------------------------
int max_stage_number = 2;
int current_stage = 0;

int stage_wave_max_number[] = { 4,4,3,2 };
int current_wave = 0;

int stage_wave_spawn_enemy_number[] = { 6,5,4,2 };

rank_entry_t rankings[MAX_RANK];
int rank_count = 0;

game_state_t gm_state;

void init_game(game_state_t* gm_state) {
    gm_state->current_stage = 0;
    gm_state->g_cat_life = 5;
    gm_state->game_clear = false;
    gm_state->gm_start_time = al_get_time();
    gm_state->gm_end_time = 0;
    // printf("debug - init_game : start time %f\n", gm_state->gm_start_time);
}


void is_game_over(game_state_t* gm_state) {
    if (gm_state->g_cat_life <= 0) {
        gm_state->game_over = true;
        // printf("debug - game over: life depleted\n");
        return true;  // ������ ����� 0�̸� ����
    }
    return false;
}

void is_game_clear(game_state_t* gm_state) {
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
    if (!fp) return;   // �ش� ���� ������ ����
    rank_count = 0;
    while (fscanf(fp, "%19s %f", rankings[rank_count].name, &rankings[rank_count].time) == 2) { // �̸� ���ڿ� + ���(float) �� ���� ��� ���������� �о��� ���� ó��
        rank_count++;
        if (rank_count >= MAX_RANK) break;
    }
    fclose(fp);

}
/*
ranking.txt ����

�ٸ��� �̸� �ð� �о �迭�� ����

�ִ� 10������ ����

���� �ݰ� ��*/

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
������ ��� (time == -1) �� ��ŷ �� �ڷ� ���� ��

������ ��ϳ����� ���� �ð� ������ ����
*/

void add_score(const char* name, float time) {
    // �ڸ� ���� ������ �׳� �߰�
    if (rank_count < MAX_RANK) {
        strncpy(rankings[rank_count].name, name, MAX_NAME_LEN);
        rankings[rank_count].time = time;
        rank_count++;
    }
    else {
        // �� �� ���: ���� ����� �ִ��� ���� ã��
        int fail_index = -1;
        for (int i = 0; i < MAX_RANK; i++) {
            if (rankings[i].time < 0) {
                fail_index = i;
                break;
            }
        }

        if (fail_index != -1) {
            // ���� ����� �ִٸ�, ������ �����
            strncpy(rankings[fail_index].name, name, MAX_NAME_LEN);
            rankings[fail_index].time = time;
        }
        else {
            // ���� ��� ������, �־��� ���� ��ϰ� ��
            int worst_index = MAX_RANK - 1;
            float worst_time = rankings[worst_index].time;

            if (time < 0) return; // ������ ����� ����
            if (time >= worst_time) return; // �� ���� ����̸� ����

            // �����
            strncpy(rankings[worst_index].name, name, MAX_NAME_LEN);
            rankings[worst_index].time = time;
        }
    }

    // ����
    qsort(rankings, rank_count, sizeof(rank_entry_t), compare_scores);
}


// ȭ�鿡 ��ŷ ����ϴ� �Լ�

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
                "%2d. %-10s  --��", i + 1, rankings[i].name);
        }
        else {
            al_draw_textf(font, al_map_rgb(255, 255, 255), 610, 300 + i * 30, 0,
                "%2d. %-10s  %.2f��", i + 1, rankings[i].name, rankings[i].time);
        }
    }

    al_flip_display();
}





int life = 5;

void apply_damage(int damage)
{
	life -= damage;

	DEBUG_PRINT("충돌 발생 life -> %d\n", life);

	if (life <= 0) {
		// TODO: 게임오버 처리하기
		DEBUG_PRINT("게임 종료\n");
	}
}