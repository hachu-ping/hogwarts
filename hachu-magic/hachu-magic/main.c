

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

#include <allegro5/keycodes.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>



int g_frames = 0;


int main() {
    // 알레그로 초기화
    init_allegro();

    // 에드온 초기화
    init_addons();
    install_driver();
    

    // 데이터 초기화
    init_data();

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
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
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

   
    // 게임 시작
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;

    while (!is_done) {
        g_frames += 1;
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        keyboard_update(&event);  // 키 상태 갱신

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // 창 종료
            is_done = true;
            break;

        case ALLEGRO_EVENT_TIMER:
            // === 상태별 업데이트 ===
            should_redraw = true;
            if (should_redraw) {
                should_redraw = false;
                if (g_scene_screne == SCENE_TITLE) {
                    draw_title_screen();
                    should_redraw = true;
                    break;
                }
     
                //else if (g_scene == SCENE_PLAY)  refresh_screen();
                else if (g_scene_screne == SCENE_PLAY) {
                    printf("3 \n");
                    // 매 프레임마다 처리합니다.

                    // *** 게임 상태 업데이트
                    // - 고양이 액션 (입력 처리)
                    update_cat();

                    // - 적 생성
                    spawn_wave();

                    // - 마법 탄환 이동
                    move_magic();
                    // - 적 이동
                    move_enemy();

                    // - 적-마법 충돌 처리
                    collide_magic();
                    // - 적-고양이 충돌 처리
                    should_redraw = true; 
                    break;
                }
                else if (g_scene_screne == SCENE_RANK)  draw_rank_screen();
                al_flip_display();
            }

            
            // TITLE/RANK는 여기서 특별한 업데이트가 없다면 생략
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
            float mx = event.mouse.x;
            float my = event.mouse.y;
            if (g_scene_screne == SCENE_TITLE) {
                if (point_in_button(mx, my, &g_btn_start)) {
                    // 플레이 시작 직전 초기화가 필요하면 여기서!
                    // ex) reset_score(); reset_entities(); init_level();
                    g_scene_screne = SCENE_PLAY;
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                }
            }
            else if (g_scene_screne == SCENE_RANK) {
                // 필요 시 클릭으로 스크롤/선택 등
            }
        } break;

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
                }
            }
            break;

        default:
            break;

        }
 
        // *** 게임 화면 업데이트
        // 값 수정 사항이 있을 때 + event 처리가 완료되었을 때 게임 화면 업데이트
        if (should_redraw && al_is_event_queue_empty(queue)) {
            should_redraw = false;

            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
                al_flip_display();
            }
            else if (g_scene_screne == SCENE_PLAY) {
                // 당신이 이미 가진 전체 게임 그리기 함수
                refresh_screen();
                al_flip_display();
            }
            else if (g_scene_screne == SCENE_RANK) {
                draw_rank_screen();
                al_flip_display();
            }
        }

    }

    if (g_font) al_destroy_font(g_font);
    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}


