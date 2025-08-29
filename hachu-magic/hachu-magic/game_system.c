
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <ctype.h> 

#include "game_system.h"


// --- keyboard ---


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

        //printf("DEBUG -- Key 눌림: %d\n", event->keyboard.keycode);  // ← 어떤 키인지 출력
        g_key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        //printf("DEBUG -- Key 눌림: %d\n", event->keyboard.keycode);  // ← 어떤 키인지 출력
        break;
    case ALLEGRO_EVENT_KEY_UP:
        // printf("DEBUG -- Key 떼짐: %d\n", event->keyboard.keycode);  // ← 어떤 키인지 출력
        g_key[event->keyboard.keycode] &= ~KEY_DOWN;
        //printf("DEBUG -- Key 떼짐: %d\n", event->keyboard.keycode);  // ← 어떤 키인지 출력
        break;
    }
}

Scene         g_scene_screne = SCENE_TITLE;     // 유일한 정의
ALLEGRO_FONT* g_font = NULL;            // 폰트는 run-time에 실제 생성
ALLEGRO_FONT* g_font_btn = NULL;
Button        g_btn_start = { 550, 380, 300, 60, "게임 시작" };
Button        g_btn_rank = { 550, 460, 300, 60, "랭크 보기" };


void draw_title_screen(void)
{
    al_clear_to_color(al_map_rgb(20, 20, 25));
    textbox_draw(&g_name_box, g_font_btn /* 또는 g_font */);
    al_draw_text(g_font, al_map_rgb(255, 255, 255), 700, 250, ALLEGRO_ALIGN_CENTRE, "CAT vs MICE");

    al_draw_filled_rectangle(g_btn_start.x, g_btn_start.y, g_btn_start.x + g_btn_start.w, g_btn_start.y + g_btn_start.h, al_map_rgb(60, 120, 250));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), g_btn_start.x + g_btn_start.w / 2, g_btn_start.y + 20, ALLEGRO_ALIGN_CENTRE, g_btn_start.label);

    al_draw_filled_rectangle(g_btn_rank.x, g_btn_rank.y, g_btn_rank.x + g_btn_rank.w, g_btn_rank.y + g_btn_rank.h, al_map_rgb(80, 180, 120));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), g_btn_rank.x + g_btn_rank.w / 2, g_btn_rank.y + 20, ALLEGRO_ALIGN_CENTRE, g_btn_rank.label);

    al_draw_text(g_font, al_map_rgb(200, 200, 200), 700, 560, ALLEGRO_ALIGN_CENTRE, "Enter: start   R: rank   ESC: end");
}

void draw_rank_screen(void)
{
    al_clear_to_color(al_map_rgb(25, 20, 20));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), 700, 150, ALLEGRO_ALIGN_CENTRE, "RANKING");
    // TODO: 실제 랭킹 목록 렌더링
    al_draw_text(g_font, al_map_rgb(200, 200, 200), 700, 520, ALLEGRO_ALIGN_CENTRE, "ESC: back");
}

TextBox g_name_box;



// 그리기 (깜박이는 커서는 타임기반)
void textbox_draw(const TextBox* tb, ALLEGRO_FONT* font) {
    // 박스 배경/테두리
    ALLEGRO_COLOR bg = tb->focused ? al_map_rgb(35, 40, 55) : al_map_rgb(28, 30, 40);
    ALLEGRO_COLOR brd = tb->focused ? al_map_rgb(90, 150, 255) : al_map_rgb(80, 80, 90);
    al_draw_filled_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, bg);
    al_draw_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, brd, 2.0f);

    // 텍스트(왼쪽 패딩)
    float pad = 10.0f;
    al_draw_text(font, al_map_rgb(255, 255, 255), tb->x + pad, tb->y + (tb->h - al_get_font_line_height(font)) / 2.0f, 0, tb->text[0] ? tb->text : "이름을 입력하세요");

    // 커서 깜박임 (0.5초 간격)
    if (tb->focused) {
        bool on = ((int)(al_get_time() * 2.0)) % 2 == 0;
        if (on) {
            // 텍스트 폭 계산해서 커서 위치 잡기
            float tw = al_get_text_width(font, tb->text);
            float cx = tb->x + pad + tw + 2.0f;
            float cy1 = tb->y + 8.0f, cy2 = tb->y + tb->h - 8.0f;
            al_draw_line(cx, cy1, cx, cy2, al_map_rgb(255, 255, 255), 1.0f);
        }
    }
}

// 이벤트 처리 (마우스 포커싱 + 키 입력)
// - ASCII만 다룹니다(영문/숫자/기호).
bool textbox_handle_event(TextBox* tb, const ALLEGRO_EVENT* ev) {
    bool changed = false;

    switch (ev->type) {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
        float mx = ev->mouse.x, my = ev->mouse.y;
        bool inside = (mx >= tb->x && mx <= tb->x + tb->w && my >= tb->y && my <= tb->y + tb->h);
        bool prev = tb->focused;
        tb->focused = inside;
        changed = (tb->focused != prev); // 테두리 색 등 변화
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
            // 엔터 → 포커스 해제(선택사항)
            tb->focused = false;
            changed = true;
        }
        else {
            int ch = ev->keyboard.unichar;
            // 간단히 ASCII 인쇄 가능한 문자만 허용
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

void textbox_clear(TextBox* tb)
{
    tb->len = 0;
    tb->text[0] = '\0';
    tb->focused = false;
}

void handle_start_from_title(ALLEGRO_EVENT_QUEUE* main_queue) {
    if (g_name_box.len > 0) STRCPY_SAFE(g_player_name, g_name_box.text);
    else                    STRCPY_SAFE(g_player_name, "guset");
    g_player_name[sizeof(g_player_name) - 1] = '\0';

    textbox_clear(&g_name_box);
    //start_play_stage(main_queue);
}