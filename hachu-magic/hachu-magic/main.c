

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>

#include "cat.h"
#include "enemy.h"
#include "fx.h"
#include "initializer.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"

#include <allegro5/keycodes.h>


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


    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

   
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
            handle_magic_collision();

            // - 적-고양이 충돌 처리
            handle_enemy_collision();

            update_explosion();

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
    
    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}


