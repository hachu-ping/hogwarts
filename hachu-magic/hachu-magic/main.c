

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
    // �˷��׷� �ʱ�ȭ
    init_allegro();


    // **********************************
    // �۲� �ֵ�� �ʱ�ȭ
     al_init_font_addon();
     al_init_ttf_addon();
    // **********************************
    
    // ����� �ʱ�ȭ
    init_addons();
    install_driver();

    // ������ �ʱ�ȭ
    init_data();

    // ***********************************
    ALLEGRO_FONT *font = al_load_ttf_font("NanumGothic.ttf", 24, 0); 
    // ALLEGRO_FONT* font = al_create_builtin_font();  // ���� �⺻ ��Ʈ ���  
    if (!font) {
        fprintf(stderr, "��Ʈ �ε� ����!\n");
        return -1;
    }
    // **********************************
    // ���ҽ� �ʱ�ȭ
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    // �̺�Ʈ ť ���
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

   
    // ���� ����
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;

    GameState gm_state;
    // 1. ���� ���� �ʱ�ȭ
    init_game(&gm_state);

   
    // 2. ���� Ŭ���� ���� Ȯ�� (������)
    gm_state.current_stage = 3;     // ���� �������� �Ϸ��ߴٰ� ����
    gm_state.g_cat_life = 3;        // ���� ����
    is_game_clear(&gm_state);     

    is_game_over(&gm_state);

    load_rankings();

    /*
    // ���� ���� ���� ? ������ ��ŷ �׽�Ʈ
    add_score("TesterA", 15.23f);  // ���� �̸��� �ð� �߰�
    add_score("TesterB", -1.0f);
    add_score("TesterC", 10.5f);
   */
    is_game_clear(&gm_state);  // ���� �ð� ���

    add_score("test", gm_state.time_taken);

    save_rankings();
 
 
    // ��ŷ ȭ�� ���
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

        keyboard_update(&event);  // Ű ���� ����

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // â ����
            is_done = true;
            break;

        case ALLEGRO_EVENT_TIMER:
            // �� �����Ӹ��� ó���մϴ�.

            // *** ���� ���� ������Ʈ
            // - ����� �׼� (�Է� ó��)
            update_cat();

            // - �� ����
            spawn_wave();

            // - ���� źȯ �̵�
            move_magic();
            // - �� �̵�
            move_enemy();

            // - ��-���� �浹 ó��
            collide_magic();
            // - ��-����� �浹 ó��

            should_redraw = true;
            break;

        default:
            break;

        }
        
    
        // *** ���� ȭ�� ������Ʈ
        // �� ���� ������ ���� �� + event ó���� �Ϸ�Ǿ��� �� ���� ȭ�� ������Ʈ
        if (should_redraw && al_is_event_queue_empty(queue)) {

            refresh_screen();

            should_redraw = false;
        }

    }
    // ********************************
    // ���� ���� ������ ��ŷ�� 10�ʰ� ȭ�鿡 ����ϰ� �����ֱ�
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


