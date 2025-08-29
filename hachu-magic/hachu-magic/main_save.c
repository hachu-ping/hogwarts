

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
    // �˷��׷� �ʱ�ȭ
    init_allegro();

    // ����� �ʱ�ȭ
    init_addons();
    install_driver();
    

    // ������ �ʱ�ȭ
    init_data();

    // ���ҽ� �ʱ�ȭ

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
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    int i = 1;

    bool is_done = false;
    bool should_redraw = false;

    while (!is_done) {
        ALLEGRO_EVENT event;
        
        al_wait_for_event(queue, &event);
        
        keyboard_update(&event);  // Ű ���� ����
        
        if (i) {
            draw_title_screen();
            al_flip_display();
            i = 0;
        }
        

        

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            // â ����
            is_done = true;
            break;
        //TODO : �̵��� �Լ��� ������.
        //TODO : switch�� g_scene_screne ����

        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            {
        
            float mx = event.mouse.x;
            float my = event.mouse.y;
            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
                if (point_in_button(mx, my, &g_btn_start)) {
                    // �÷��� ���� ���� �ʱ�ȭ�� �ʿ��ϸ� ���⼭!
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
                // �ʿ� �� Ŭ������ ��ũ��/���� ��
            }}
            break;
         //TODO : key�� ȭ�� if�� �ٲٱ�, switch case
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
                    should_redraw = true;
                }
            }
            break;

        default:
            break;

        }

 
        // *** ���� ȭ�� ������Ʈ
        // �� ���� ������ ���� �� + event ó���� �Ϸ�Ǿ��� �� ���� ȭ�� ������Ʈ
        if (al_is_event_queue_empty(queue)) {

            if (g_scene_screne == SCENE_TITLE) {
                draw_title_screen();
            }
            else if (g_scene_screne == SCENE_PLAY) {
                // ����� �̹� ���� ��ü ���� �׸��� �Լ�
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


