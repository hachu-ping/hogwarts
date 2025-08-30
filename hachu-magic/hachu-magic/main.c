

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
    // �˷��׷� �ʱ�ȭ
    init_allegro();

    // ����� �ʱ�ȭ
    init_addons();
    install_driver();

    // ������ �ʱ�ȭ
    init_data();

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
            handle_magic_collision();

            // - ��-����� �浹 ó��
            handle_enemy_collision();

            update_explosion();

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
    
    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}


