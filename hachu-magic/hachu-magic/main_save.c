

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
#include "enemy.h"
#include "magic.h"
#include "cat.h"
#include "game_system.h"
#include "game_manager.h"

#include <allegro5/keycodes.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


int main() {
    // 알레그로 초기화
    init_allegro();

    // 에드온 초기화
    init_addons();
    install_driver();
    

    // 데이터 초기화
    init_data();

    // 리소스 초기화

    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();
    //ALLEGRO_FONT* g_font = init_builtin_font();
    g_font = al_create_builtin_font();
    //Scene g_scene_screne = SCENE_TITLE;
    //ALLEGRO_FONT* font = NULL;  // 내장 폰트(별도 TTF 없이)
   // static Button g_btn_start = { 550, 380, 300, 60, "게임 시작" };
    //static Button g_btn_rank = { 550, 460, 300, 60, "랭크 보기" };


    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    int i = 1;

    bool is_done = false;
    bool should_redraw = false;

    while (!is_done) {
        ALLEGRO_EVENT event;
        
        al_wait_for_event(queue, &event);
        
        keyboard_update(&event);  // 키 상태 갱신
        
        if (i) {
            draw_title_screen();
            al_flip_display();
            i = 0;
        }
        

        

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // 창 종료
            is_done = true;
            break;
        //TODO : 이동은 함수로 ㅂ빼자.
        //TODO : switch로 g_scene_screne 구분

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            {
        
            float mx = event.mouse.x;
            float my = event.mouse.y;
            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
                if (point_in_button(mx, my, &g_btn_start)) {
                    // 플레이 시작 직전 초기화가 필요하면 여기서!
                    // ex) reset_score(); reset_entities(); init_level();
                    g_scene_screne = SCENE_PLAY;
                    printf("1\n");
                    al_pause_event_queue(queue, true);
                    play_game();
                    al_pause_event_queue(queue, false);
                    g_scene_screne = SCENE_TITLE;
                    should_redraw = true;
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                    should_redraw = true;
                }
            }
            else if (g_scene_screne == SCENE_RANK) {
                // 필요 시 클릭으로 스크롤/선택 등
            }}
            break;
         //TODO : key랑 화면 if문 바꾸기, switch case
        case ALLEGRO_EVENT_KEY_DOWN:
            if (g_scene_screne == SCENE_TITLE) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    // 키보드로도 시작
                    g_scene_screne = SCENE_PLAY;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                    g_scene_screne = SCENE_RANK;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    is_done = true; // 타이틀에서 ESC로 종료
                }
            }
            else if (g_scene_screne == SCENE_PLAY) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    // 플레이 중 ESC → 타이틀 복귀(또는 일시정지 메뉴)
                    g_scene_screne = SCENE_TITLE;
                }
            }
            else if (g_scene_screne == SCENE_RANK) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    g_scene_screne = SCENE_TITLE;
                    should_redraw = true;
                }
            }
            break;

        default:
            break;

        }

 
        // *** 게임 화면 업데이트
        // 값 수정 사항이 있을 때 + event 처리가 완료되었을 때 게임 화면 업데이트
        if (al_is_event_queue_empty(queue)) {

            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
            }
            else if (g_scene_screne == SCENE_PLAY) {
                // 당신이 이미 가진 전체 게임 그리기 함수
                refresh_screen();
            }
            else if (g_scene_screne == SCENE_RANK) {
                draw_rank_screen();
            }               
            al_flip_display();

        }
     
    }

    if (g_font) al_destroy_font(g_font);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}


