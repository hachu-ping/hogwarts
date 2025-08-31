
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
#include "fx.h"
#include "initializer.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"
#include "game_manager.h"

#include <allegro5/keycodes.h>


int g_frames = 0;
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

    // 데이터 초기화
    init_data();

    ALLEGRO_FONT* font = al_load_ttf_font("NanumGothic.ttf", 24, 0);
    // ALLEGRO_FONT* font = al_create_builtin_font();  // ���� �⺻ ��Ʈ ���  
    if (!font) {
        fprintf(stderr, "��Ʈ �ε� ����!\n");
        return -1;
    }

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    // 이벤트 큐 등록
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

   
    // 타이머 시작
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;


    while (!is_done) {
        g_frames += 1;
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        keyboard_update(&event);  // 키 입력 처리

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // 창 닫기
            is_done = true;
            break;

        case ALLEGRO_EVENT_TIMER:
            // 게임 로직마다 처리합니다.

            // *** 게임 로직 업데이트
            // - 플레이어 액션 (입력 처리)
            update_cat();

            // - 적 생성
            spawn_wave();

            // - 마법 탄환 이동
            move_magic();

            // - 적 이동
            move_enemy();

            // - 적-마법 충돌 처리
            handle_magic_collision();

            // - 적-플레이어 충돌 처리
            handle_enemy_collision();

            update_explosion();

            should_redraw = true;
            break;

        default:
            break;

        }
 
        // *** 화면 그리기 업데이트
        // 게임 로직 업데이트 완료 후 + event 처리가 완료되었을 때 화면 그리기 업데이트
        if (should_redraw && al_is_event_queue_empty(queue)) {

            refresh_screen();

            should_redraw = false;
        }

    }
    

    load_rankings();
    add_score("test", gm_state.time_taken);
    save_rankings();

    // ��ŷ ȭ�� ���
    al_clear_to_color(al_map_rgb(0, 0, 0));

    print_rankings_screen(font, &gm_state);
    al_flip_display();

    al_rest(15.0);

    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    

    return 0;
}

