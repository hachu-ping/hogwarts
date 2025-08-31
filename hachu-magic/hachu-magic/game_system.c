#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <ctype.h> 

#include "game_system.h"
#include "sprites.h"

extern sprites_t sprites;

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


text_box_t g_name_box;

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

void prepare_game_start() {
    if (g_name_box.len > 0) STRCPY_SAFE(get_game_state()->player_name, g_name_box.text);
    else                    STRCPY_SAFE(get_game_state()->player_name, "guset");
    g_player_name[sizeof(get_game_state()->player_name) - 1] = '\0';

    textbox_clear(&g_name_box);
}