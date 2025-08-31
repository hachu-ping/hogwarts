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
#include "enemy.h"
#include "fx.h"
#include "game_system.h"
#include "game_manager.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"
#include "game_manager.h"

ALLEGRO_FONT* font_hud;
ALLEGRO_FONT* font_stage;
extern int rank_count;
extern rank_entry_t rankings[];
extern game_state_t gm_state;

int main() {
    // 알레그로 초기화
    init_allegro();

    al_init_font_addon();
    al_init_ttf_addon();
    // 애드온 초기화
    init_addons();
    install_driver();

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(32), "reserve samples");  //샘플의 키홀드값

    // 데이터 초기화
    init_data();

    ALLEGRO_FONT* font = al_load_ttf_font("assets/fonts/DotGothic16-Regular.ttf", 24, 0);
    ALLEGRO_FONT* font_title = al_load_ttf_font("assets/fonts/DotGothic16-Regular.ttf", 24, 0);
    // ALLEGRO_FONT* font = al_create_builtin_font();  // 기본 내장 폰트 사용  
    if (!font) {
        fprintf(stderr, "폰트 로드 실패!\n");
        return -1;
    }

     font_hud = al_load_ttf_font("assets/fonts/DotGothic16-Regular.ttf", 35, 0);
    if (!font_hud) {
        fprintf(stderr, "폰트 로드 실패!\n");
        return -1;
    }
    font_stage = al_load_ttf_font("assets/fonts/DotGothic16-Regular.ttf", 55, 0);
    if (!font_stage) {
        fprintf(stderr, "폰트 로드 실패!\n");
        return -1;
    }

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    textbox_init(&g_name_box, g_btn_start.x, g_btn_start.y - 60, g_btn_start.w, 40, 32);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();



    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // 첫 화면
    g_scene_screne = SCENE_TITLE;
    draw_title_screen(font, font_title);
    al_flip_display();

    // TODO: 등수 로딩하는 코드, 이거 나중에 위치 옮기기
    load_rankings();

    bool is_done = false;

    play_sound(GAME_SOUND_BACKGROUND, 0);

    while (!is_done) {
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);
        keyboard_update(&event);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // 창 닫기
            is_done = true;
            break;
            //TODO : 이동할 함수를 만들자.
            //TODO : switch문 g_scene_screne 기준

                // 메인타이틀화면 텍스트박스/버튼 입력 처리: 마우스/키보드 입력을 둘 다하여야함
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR: {
            if (g_scene_screne != SCENE_TITLE) break;

            bool changed = false;

            // 1) 텍스트박스에 대한 이벤트 처리(포커스/문자 입력)
            changed |= textbox_handle_event(&g_name_box, &event);

            // 2) 마우스 클릭이면 버튼 처리
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.mouse.x, my = event.mouse.y;

                if (point_in_button(mx, my, &g_btn_start)) {
                    handle_start_from_title(queue);  // 플 이름 설정(빈 값은 guset) + 초기화 + 시작
                    printf("%s\n", g_player_name);
                    start_play_stage(queue);

                    g_scene_screne = SCENE_RANK;

                    changed = true;                  // 타이틀 재그리기
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                    changed = true;
                }
            }
            // 3) 키보드입력: 엔터로 시작
            else { // ALLEGRO_EVENT_KEY_CHAR
                int key = event.keyboard.keycode;
                if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_PAD_ENTER) {
                    handle_start_from_title(queue);  // 플 시작 처리
                    printf("%s\n", g_player_name);
                    start_play_stage(queue);
                    changed = true;
                }
            }

            if (changed) {
                if (g_scene_screne == SCENE_TITLE)      draw_title_screen(font, font_title);
                else if (g_scene_screne == SCENE_RANK)  print_rankings_screen(font, &gm_state);
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
                    draw_title_screen(font, font_title);
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
    al_destroy_font(font_hud);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    return 0;
}