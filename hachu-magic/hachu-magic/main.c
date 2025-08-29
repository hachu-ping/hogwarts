#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>

#include "cat.h"
#include "enemy.h"
#include "initializer.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"
#include "game_system.h"
#include "game_manager.h"

#include <allegro5/keycodes.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#if defined(_MSC_VER)
#define STRCPY_SAFE(dst, src) strncpy_s(dst, sizeof(dst), src, _TRUNCATE)
#else
#define STRCPY_SAFE(dst, src) snprintf(dst, sizeof(dst), "%s", src)
#endif


int main() {
    // Allegro / addons
    init_allegro();
    init_addons();
    install_driver();

    init_data();

    // 버튼 위에 텍스트박스 배치
    textbox_init(&g_name_box, g_btn_start.x, g_btn_start.y - 60, g_btn_start.w, 40, 32);

    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();

    g_font = al_create_builtin_font();
    g_font_btn = al_create_builtin_font();

    // 이벤트 소스 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // 첫 화면
    g_scene_screne = SCENE_TITLE;
    draw_title_screen();
    al_flip_display();

    bool is_done = false;

    while (!is_done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        keyboard_update(&event);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            is_done = true;
            break;

            // ★ 타이틀에서 텍스트박스/버튼 입력 처리: 마우스/문자 입력을 한 블록에서
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR: {
            if (g_scene_screne != SCENE_TITLE) break;

            bool changed = false;

            // 1) 텍스트박스에 먼저 이벤트 전달(포커스/문자 편집)
            changed |= textbox_handle_event(&g_name_box, &event);

            // 2) 마우스 클릭이면 버튼 처리
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.mouse.x, my = event.mouse.y;

                if (point_in_button(mx, my, &g_btn_start)) {
                    // 이름 저장 후 게임 시작
                    STRCPY_SAFE(g_player_name, g_name_box.text);
                    g_player_name[sizeof(g_player_name) - 1] = '\0';
                    textbox_clear(&g_name_box);
                    start_play_stage(queue);     // 내부에서 play_game 실행/복귀
                    printf("%s", g_player_name);
                    changed = true;              // 타이틀로 복귀했으니 다시 그리기
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                    changed = true;
                }
            }
            // 3) 문자 입력이면(Enter로 시작 등) 추가 처리
            else {
                int key = event.keyboard.keycode;
                if ((key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_PAD_ENTER) && g_name_box.len > 0) {
                    STRCPY_SAFE(g_player_name, g_name_box.text);
                    g_player_name[sizeof(g_player_name) - 1] = '\0';
                    textbox_clear(&g_name_box);
                    printf("%s", g_player_name);
                    start_play_stage(queue);
                    changed = true;
                }
            }

            if (changed) {
                if (g_scene_screne == SCENE_TITLE)      draw_title_screen();
                else if (g_scene_screne == SCENE_RANK)  draw_rank_screen();
                al_flip_display();
            }
        } break;


        case ALLEGRO_EVENT_KEY_DOWN: {
            int k = event.keyboard.keycode;
            switch (k) {
            case ALLEGRO_KEY_ESCAPE:
                if (g_scene_screne == SCENE_TITLE) {
                    is_done = true;
                }
                else {
                    g_scene_screne = SCENE_TITLE;
                    draw_title_screen();
                    al_flip_display();
                }
                break;
            default: break;
            }
        } break;

        default:
            break;
        }
    }

    if (g_font)     al_destroy_font(g_font);
    if (g_font_btn) al_destroy_font(g_font_btn);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    return 0;
}
