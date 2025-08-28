#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "initializer.h"
#include "utils.h"


#include <allegro5/keycodes.h>

#include "utils.h"


// ----------------------------------------------------------------------------------------------------------------------------------------
extern unsigned char key[ALLEGRO_KEY_MAX];

int main() {
    // 알레그로 초기화
    init_allegro();

    // 에드온 초기화
    init_addons();
    install_driver();
    memset(key, 0, sizeof(key));
    cat_init();

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());


    // load placeholder image
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background-image");
   
    //al_draw_bitmap(background, 0, 0, 0);
    al_draw_scaled_bitmap(background, 0, 0, 640, 437, 0, 0, 1400, 800, 0); // 이미지 크기 배경으로 맞추기
 
    // 게임 시작
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;


    while (!is_done) {

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

            // - 적 생성

            // - 마법 탄환 이동

            // - 적 이동

            // - 적-마법 충돌 처리

            // - 적-고양이 충돌 처리
            cat_update();

            should_redraw = true;
            break;

        default:
            break;

        }
 
        // *** 게임 화면 업데이트
        // 값 수정 사항이 있을 때 + event 처리가 완료되었을 때 게임 화면 업데이트
        if (should_redraw && al_is_event_queue_empty(queue)) {

            // 배경 그리기

            // 적 그리기

            // 파티클 (FX) 그리기

            // 캐릭터 그리기
            cat_draw();
            // 마법 탄환 그리기

            al_flip_display();
            should_redraw = false;
        }

    }

    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}

