#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <ctype.h> 

#include "game_system.h"
#include "sprites.h"

extern sprites_t g_sprites;

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

        //printf("DEBUG -- Key 누름: %d\n", event->keyboard.keycode);  // 어떤 키 누르는지 확인
        g_key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        //printf("DEBUG -- Key 누름: %d\n", event->keyboard.keycode);  // 어떤 키 누르는지 확인
        break;
    case ALLEGRO_EVENT_KEY_UP:
        // printf("DEBUG -- Key 뗌: %d\n", event->keyboard.keycode);  // 어떤 키 뗐는지 확인
        g_key[event->keyboard.keycode] &= ~KEY_DOWN;
        //printf("DEBUG -- Key 뗌: %d\n", event->keyboard.keycode);  // 어떤 키 뗐는지 확인
        break;
    }
}

Scene         g_scene_screne = SCENE_TITLE;     // 현재 화면
ALLEGRO_FONT* g_font = NULL;            // 폰트는 run-time에 동적 로드
ALLEGRO_FONT* g_font_btn = NULL;
Button        g_btn_start = { 550, 380, 300, 60, "게임 시작" };
Button        g_btn_rank = { 550, 460, 300, 60, "랭크 보기" };

Button        g_btn_start = { 550, 380, 300, 60, "start" };
Button        g_btn_rank = { 550, 460, 300, 60, "rank" };

// 버튼 안에 텍스트를 정확히 가운데 정렬해서 그려주는 유틸
static void draw_button(Button* btn, ALLEGRO_FONT* font, ALLEGRO_COLOR fill, ALLEGRO_COLOR textc, float border_px)
{
    // 1) 버튼 박스
    al_draw_filled_rectangle(btn->x, btn->y, btn->x + btn->w, btn->y + btn->h, fill);
    if (border_px > 0.0f) {
        al_draw_rectangle(btn->x, btn->y, btn->x + btn->w, btn->y + btn->h, al_map_rgb(255, 255, 255), border_px);
    }
    al_clear_to_color(al_map_rgb(20, 20, 25));
    textbox_draw(&g_name_box, g_font_btn /* 또는 g_font */);
    al_draw_text(g_font, al_map_rgb(255, 255, 255), 700, 250, ALLEGRO_ALIGN_CENTRE, "CAT vs MICE");

    // 2) 문자열 크기
    int tw = al_get_text_width(font, btn->label);
    int th = al_get_font_line_height(font);

    // 3) 가운데 좌표(가로/세로)
    float tx = btn->x + (btn->w - tw) * 0.5f;
    float ty = btn->y + (btn->h - th) * 0.5f;

    // 4) 텍스트
    al_draw_text(font, textc, tx, ty, 0, btn->label);
}

// 마우스가 버튼 위에 올라왔는지 체크 (hover 용)
static bool button_contains(const Button* btn, float mx, float my)
{
    return (mx >= btn->x && mx <= btn->x + btn->w &&
        my >= btn->y && my <= btn->y + btn->h);
}


void draw_title_screen(ALLEGRO_FONT* font, ALLEGRO_FONT* font_title)
{
	al_draw_bitmap(g_sprites.background[3], 0, 0, 0);
    //al_clear_to_color(al_map_rgb(20, 20, 25));
    textbox_draw(&g_name_box, font /* �Ǵ� g_font */);
    al_draw_text(font, al_map_rgb(255, 255, 255), 700, 250, ALLEGRO_ALIGN_CENTRE, "CAT vs MICE");

    draw_button(&g_btn_start, font, al_map_rgb(60, 120, 250), al_map_rgb(255, 255, 255), 2.0f);
    draw_button(&g_btn_rank, font, al_map_rgb(80, 180, 120), al_map_rgb(255, 255, 255), 2.0f);


    al_draw_text(font, al_map_rgb(200, 200, 200), 700, 560, ALLEGRO_ALIGN_CENTRE, "Enter: start   R: rank   ESC: end");
}

void draw_rank_screen(ALLEGRO_FONT* font)
{
    al_clear_to_color(al_map_rgb(25, 20, 20));
    al_draw_text(font, al_map_rgb(255, 255, 255), 700, 150, ALLEGRO_ALIGN_CENTRE, "RANKING");
    al_draw_text(font, al_map_rgb(200, 200, 200), 700, 520, ALLEGRO_ALIGN_CENTRE, "ESC: back");
}

TextBox g_name_box;



// 그리기 (블링킹 커서의 타이밍용)
void textbox_draw(const TextBox* tb, ALLEGRO_FONT* font) {
    // 박스 배경/테두리
    ALLEGRO_COLOR bg = tb->focused ? al_map_rgb(35, 40, 55) : al_map_rgb(28, 30, 40);
    ALLEGRO_COLOR brd = tb->focused ? al_map_rgb(90, 150, 255) : al_map_rgb(80, 80, 90);
    al_draw_filled_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, bg);
    al_draw_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, brd, 2.0f);

    // 텍스트(빈칸 패딩)
    float pad = 10.0f;
    al_draw_text(font, al_map_rgb(255, 255, 255), tb->x + pad, tb->y + (tb->h - al_get_font_line_height(font)) / 2.0f, 0, tb->text[0] ? tb->text : "player name");

    // 커서 블링킹 (0.5초 주기)
    if (tb->focused) {
        bool on = ((int)(al_get_time() * 2.0)) % 2 == 0;
        if (on) {
            // 텍스트 너비 계산해서 커서 위치 구함
            float tw = al_get_text_width(font, tb->text);
            float cx = tb->x + pad + tw + 2.0f;
            float cy1 = tb->y + 8.0f, cy2 = tb->y + tb->h - 8.0f;
            al_draw_line(cx, cy1, cx, cy2, al_map_rgb(255, 255, 255), 1.0f);
        }
    }
}

// 이벤트 처리 (마우스 포커스 + 키 입력)
// - ASCII만 다룹니다(숫자/영문/기호).
bool textbox_handle_event(TextBox* tb, const ALLEGRO_EVENT* ev) {
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