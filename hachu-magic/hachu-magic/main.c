

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include "cat.h"
#include "enemy.h"
#include "initializer.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"
#include "game_manager.h"


#include <allegro5/keycodes.h>

int g_frames = 0;
// **************************************
extern int rank_count;
extern RankEntry rankings[];

// **************************************

int main() {
    // 알레그로 초기화
    init_allegro();


    // **********************************
    // 글꼴 애드온 초기화
     al_init_font_addon();
     al_init_ttf_addon();
    // **********************************
    
    // 에드온 초기화
    init_addons();
    install_driver();

    // 데이터 초기화
    init_data();

    // ***********************************
    ALLEGRO_FONT *font = al_load_ttf_font("NanumGothic.ttf", 24, 0); 
    // ALLEGRO_FONT* font = al_create_builtin_font();  // 내장 기본 폰트 사용  
    if (!font) {
        fprintf(stderr, "폰트 로드 실패!\n");
        return -1;
    }
    // **********************************
    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

   
    // 게임 시작
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;

    GameState gm_state;
    // 1. 게임 상태 초기화
    init_game(&gm_state);

   
    // 2. 게임 클리어 조건 확인 (디버깅용)
    gm_state.current_stage = 3;     // 최종 스테이지 완료했다고 가정
    gm_state.g_cat_life = 3;        // 생명 있음
    is_game_clear(&gm_state);     

    is_game_over(&gm_state);

    load_rankings();

    /*
    // 게임 종료 직전 ? 디버깅용 랭킹 테스트
    add_score("TesterA", 15.23f);  // 임의 이름과 시간 추가
    add_score("TesterB", -1.0f);
    add_score("TesterC", 10.5f);
   */
    is_game_clear(&gm_state);  // 종료 시간 계산

    add_score("test", gm_state.time_taken);

    save_rankings();
 
 
    // 랭킹 화면 출력
    al_clear_to_color(al_map_rgb(0, 0, 0));
    print_rankings_screen(font);
    al_flip_display();
    al_rest(15.0);

    al_destroy_font(font);
    al_destroy_display(disp);




    /*
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

        default:
            break;

        }
        
    
        // *** 게임 화면 업데이트
        // 값 수정 사항이 있을 때 + event 처리가 완료되었을 때 게임 화면 업데이트
        if (should_redraw && al_is_event_queue_empty(queue)) {

            refresh_screen();

            should_redraw = false;
        }

    }
    // ********************************
    // 게임 종료 직전에 랭킹을 10초간 화면에 출력하고 보여주기
    al_clear_to_color(al_map_rgb(0, 0, 0));
    print_rankings_screen(font);
    al_flip_display();
    al_rest(10.0);
    al_destroy_font(font);
// *************************************
    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    */
    return 0;
}


