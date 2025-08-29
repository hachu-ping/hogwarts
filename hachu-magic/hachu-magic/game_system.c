
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

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
Button        g_btn_start = { 550, 380, 300, 60, "게임 시작" };
Button        g_btn_rank = { 550, 460, 300, 60, "랭크 보기" };


void draw_title_screen(void) 
{
    al_clear_to_color(al_map_rgb(20, 20, 25));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), 700, 250, ALLEGRO_ALIGN_CENTRE, "CAT vs MICE");

    al_draw_filled_rectangle(g_btn_start.x, g_btn_start.y, g_btn_start.x + g_btn_start.w, g_btn_start.y + g_btn_start.h, al_map_rgb(60, 120, 250));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), g_btn_start.x + g_btn_start.w / 2, g_btn_start.y + 20, ALLEGRO_ALIGN_CENTRE, g_btn_start.label);

    al_draw_filled_rectangle(g_btn_rank.x, g_btn_rank.y, g_btn_rank.x + g_btn_rank.w, g_btn_rank.y + g_btn_rank.h, al_map_rgb(80, 180, 120));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), g_btn_rank.x + g_btn_rank.w / 2, g_btn_rank.y + 20, ALLEGRO_ALIGN_CENTRE, g_btn_rank.label);

    al_draw_text(g_font, al_map_rgb(200, 200, 200), 700, 560, ALLEGRO_ALIGN_CENTRE, "Enter: 시작   R: 랭크   ESC: 종료");
}

void draw_rank_screen(void)
{
    al_clear_to_color(al_map_rgb(25, 20, 20));
    al_draw_text(g_font, al_map_rgb(255, 255, 255), 700, 150, ALLEGRO_ALIGN_CENTRE, "RANKING");
    // TODO: 실제 랭킹 목록 렌더링
    al_draw_text(g_font, al_map_rgb(200, 200, 200), 700, 520, ALLEGRO_ALIGN_CENTRE, "ESC: 뒤로가기");
}
