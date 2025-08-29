

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
    //ALLEGRO_FONT* g_font = init_builtin_font();
    g_font = al_create_builtin_font();
    //Scene g_scene_screne = SCENE_TITLE;
    //ALLEGRO_FONT* font = NULL;  // ���� ��Ʈ(���� TTF ����)
   // static Button g_btn_start = { 550, 380, 300, 60, "���� ����" };
    //static Button g_btn_rank = { 550, 460, 300, 60, "��ũ ����" };


    // �̺�Ʈ ť ���
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

   
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
            // === ���º� ������Ʈ ===
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
                }
                else if (g_scene_screne == SCENE_RANK)  draw_rank_screen();
                al_flip_display();
            }

            
            // TITLE/RANK�� ���⼭ Ư���� ������Ʈ�� ���ٸ� ����
            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
            float mx = event.mouse.x;
            float my = event.mouse.y;
            if (g_scene_screne == SCENE_TITLE) {
                if (point_in_button(mx, my, &g_btn_start)) {
                    // �÷��� ���� ���� �ʱ�ȭ�� �ʿ��ϸ� ���⼭!
                    // ex) reset_score(); reset_entities(); init_level();
                    g_scene_screne = SCENE_PLAY;
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                }
            }
            else if (g_scene_screne == SCENE_RANK) {
                // �ʿ� �� Ŭ������ ��ũ��/���� ��
            }
        } break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (g_scene_screne == SCENE_TITLE) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    // Ű����ε� ����
                    g_scene_screne = SCENE_PLAY;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_R) {
                    g_scene_screne = SCENE_RANK;
                }
                else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    is_done = true; // Ÿ��Ʋ���� ESC�� ����
                }
            }
            else if (g_scene_screne == SCENE_PLAY) {
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    // �÷��� �� ESC �� Ÿ��Ʋ ����(�Ǵ� �Ͻ����� �޴�)
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
 
        // *** ���� ȭ�� ������Ʈ
        // �� ���� ������ ���� �� + event ó���� �Ϸ�Ǿ��� �� ���� ȭ�� ������Ʈ
        if (should_redraw && al_is_event_queue_empty(queue)) {
            should_redraw = false;

            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
                al_flip_display();
            }
            else if (g_scene_screne == SCENE_PLAY) {
                // ����� �̹� ���� ��ü ���� �׸��� �Լ�
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


