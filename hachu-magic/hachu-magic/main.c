#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>

#include "cat.h"
#include "initializer.h"
#include "utils.h"

extern cat_t g_cat;
int g_frames = 0;

int main() {
    // �˷��׷� �ʱ�ȭ
    init_allegro();

    // ����� �ʱ�ȭ
    init_addons();
    install_driver();

    // ���ҽ� �ʱ�ȭ
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    // �̺�Ʈ ť ���
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());


    // ������ �ʱ�ȭ
    DEBUG_init_cat();
    init_sprites();

 
    // ���� ����
    al_start_timer(timer);

    bool is_done = false;
    bool should_redraw = false;


    while (!is_done) {
        g_frames += 1;
        ALLEGRO_EVENT event;

        al_wait_for_event(queue, &event);

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // â ����
            is_done = true;
            break;

        case ALLEGRO_EVENT_TIMER:
            // �� �����Ӹ��� ó���մϴ�.

            // *** ���� ���� ������Ʈ

            // - �� ����

            // - ���� źȯ �̵�

            // - �� �̵�

            // - ��-���� �浹 ó��

            // - ��-����� �浹 ó��

            should_redraw = true;
            break;

        default:
            break;
        }
 
        // *** ���� ȭ�� ������Ʈ
        // �� ���� ������ ���� �� + event ó���� �Ϸ�Ǿ��� �� ���� ȭ�� ������Ʈ
        if (should_redraw && al_is_event_queue_empty(queue)) {

            // ��� �׸���
            draw_background();

            // �� �׸���
            draw_enemies();

            // ��ƼŬ (FX) �׸���
            draw_fxs();

            // ĳ���� �׸���
            draw_cat();

            // ���� źȯ �׸���
            draw_magics();

            al_flip_display();
            should_redraw = false;
        }

    }

    al_destroy_timer(timer);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}