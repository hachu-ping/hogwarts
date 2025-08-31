#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


#include "audio.h"
#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
#include "game_system.h"
#include "game_manager.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"
#include "scene_manager.h"

ALLEGRO_FONT* font_hud;
ALLEGRO_FONT* font_stage;
extern int rank_count;
extern rank_entry_t rankings[];

int main() {
    // 알레그로 초기화
    init_allegro();

    // 알레그로 초기 설정
    init_addons();
    install_driver();

    // 데이터 초기화
    init_data();

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();




    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    play_sound(GAME_SOUND_BACKGROUND, 0);

    // 첫 화면
    change_scene(SCENE_TITLE);

    bool is_done = false;
    while (!is_done) {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);
        keyboard_update(&event);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // 창 닫기
            is_done = true;
            break;

        // 메인타이틀화면 텍스트박스/버튼 입력 처리: 마우스/키보드 입력을 둘 다하여야함
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            /* intentional fallthrough */
        case ALLEGRO_EVENT_KEY_CHAR: {
            if (get_scene_manager()->current_scene != SCENE_TITLE) break;

            bool changed = false;

            // 1) 텍스트박스에 대한 이벤트 처리(포커스/문자 입력)
            changed |= textbox_handle_event(&g_name_box, &event);

            // 2) 마우스 클릭이면 버튼 처리
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.mouse.x, my = event.mouse.y;

                if (is_pointed_in_button(mx, my, &start_button)) {
                    prepare_game_start();  // 플 이름 설정(빈 값은 guset) + 초기화 + 시작

                    DEBUG_PRINT("%s\n", get_game_state()->player_name);
                    start_play_stage(queue);

                    change_scene(SCENE_RANK);
                }
                else if (is_pointed_in_button(mx, my, &rank_button)) {
                    change_scene(SCENE_RANK);
                }
            }
            // 3) 키보드입력: 엔터로 시작
            else { // ALLEGRO_EVENT_KEY_CHAR
                int key = event.keyboard.keycode;
                if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_PAD_ENTER) {
                    prepare_game_start();  // 플 시작 처리
                    printf("%s\n", g_player_name);
                    start_play_stage(queue);
                    changed = true;
                }
            }
        } break;


        case ALLEGRO_EVENT_KEY_DOWN: 
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if (get_scene_manager()->current_scene == SCENE_TITLE) {
                    is_done = true;
                } else {
                    change_scene(SCENE_TITLE);
                }
                break;
            default: 
                break;
            }
            break;

        default:
            break;
        }
    }

    al_destroy_font(font_hud);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    return 0;
}