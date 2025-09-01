#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <ctype.h> 

#include "debug.h"
#include "game_system.h"
#include "sprites.h"

#define MAX_RANK 10
#define MAX_NAME_LEN 20
#define RANK_FILE "ranking.txt"

static int rank_count;
static rank_entry_t rankings[MAX_RANK];

unsigned char g_key[ALLEGRO_KEY_MAX];

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            g_key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        g_key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        g_key[event->keyboard.keycode] &= ~KEY_DOWN;
        break;
    }
}


static text_box_t g_name_box;

const text_box_t* get_name_box()
{
    return &g_name_box;
}

// 이벤트 처리 (마우스 포커스 + 키 입력)
// - ASCII만 다룹니다(숫자/영문/기호).
bool textbox_handle_event(text_box_t* tb, const ALLEGRO_EVENT* ev) {
    bool changed = false;

    switch (ev->type) {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
        float mx = ev->mouse.x, my = ev->mouse.y;
        bool inside = (mx >= tb->x && mx <= tb->x + tb->w && my >= tb->y && my <= tb->y + tb->h);
        bool prev = tb->focused;
        tb->focused = inside;
        changed = (tb->focused != prev); // 포커스 상태 변화
    } break;

    case ALLEGRO_EVENT_KEY_CHAR:
        if (!tb->focused) break;

        if (ev->keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
            if (tb->len > 0) {
                tb->text[--tb->len] = '\0';
                changed = true;
            }
        }
        else if (ev->keyboard.keycode == ALLEGRO_KEY_ENTER ||
            ev->keyboard.keycode == ALLEGRO_KEY_PAD_ENTER) {
            // 엔터 키 누르면 포커스 해제(완료 신호)
            tb->focused = false;
            changed = true;
        }
        else {
            int ch = ev->keyboard.unichar;
            // 출력이 가능한 ASCII 인쇄 문자만 허용
            if (ch >= 32 && ch < 127 && tb->len < tb->maxlen) {
                tb->text[tb->len++] = (char)ch;
                tb->text[tb->len] = '\0';
                changed = true;
            }
        }
        break;
    }
    return changed;
}

void textbox_clear(text_box_t* tb)
{
    tb->len = 0;
    tb->text[0] = '\0';
    tb->focused = false;
}

const rank_entry_t* get_rankings(void)
{
    return rankings;
}

int get_rank_count(void)
{
    return rank_count;
}


void load_rankings(void) {
    DEBUG_PRINT("debug - load_rankings\n");
    FILE* fp = fopen(RANK_FILE, "r");
    if (!fp) return;   // 해당 파일 존재하지 않음
    rank_count = 0;
    while (fscanf(fp, "%s %f", rankings[rank_count].name, &rankings[rank_count].time) == 2) { // 이름 문자열 + 시간(float) 두 개가 모두 성공적으로 읽어진 경우 처리
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
    DEBUG_PRINT("debug - save_rankings\n");
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
            DEBUG_PRINT("debug: %f\n", time);
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
            DEBUG_PRINT("debug: %f\n", time);
        }
    }

    // 정렬
    qsort(rankings, rank_count, sizeof(rank_entry_t), compare_scores);
}
