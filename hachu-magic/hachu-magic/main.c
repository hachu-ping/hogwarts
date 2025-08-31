

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "cat.h"
#include "enemy.h"
#include "game_system.h"
#include "game_manager.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"
#include "magic.h"
#include "game_system.h"
#include "game_manager.h"




int main() {
    // Allegro / addons
    init_allegro();
    init_addons();
    install_driver();

    init_data();

    // ��ư ���� �ؽ�Ʈ�ڽ� ��ġ
    textbox_init(&g_name_box, g_btn_start.x, g_btn_start.y - 60, g_btn_start.w, 40, 32);

    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();

    g_font = al_create_builtin_font();
    g_font_btn = al_create_builtin_font();

    // �̺�Ʈ �ҽ� ���
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // ù ȭ��
    g_scene_screne = SCENE_TITLE;
    draw_title_screen();
    al_flip_display();

    bool is_done = false;

    while (!is_done) {
        ALLEGRO_EVENT event;
        
        al_wait_for_event(queue, &event);
        keyboard_update(&event);

        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            is_done = true;
            break;
        //TODO : �̵��� �Լ��� ������.
        //TODO : switch�� g_scene_screne ����

            // ��Ÿ��Ʋ���� �ؽ�Ʈ�ڽ�/��ư �Է� ó��: ���콺/���� �Է��� �� ���Ͽ���
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR: {
            if (g_scene_screne != SCENE_TITLE) break;

            bool changed = false;

            // 1) �ؽ�Ʈ�ڽ��� ���� �̺�Ʈ ����(��Ŀ��/���� ����)
            changed |= textbox_handle_event(&g_name_box, &event);

            // 2) ���콺 Ŭ���̸� ��ư ó��
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                float mx = event.mouse.x, my = event.mouse.y;

                if (point_in_button(mx, my, &g_btn_start)) {
                    handle_start_from_title(queue);  // �� �̸� ����(�� ��� guset) + ���� + ����
                    printf("%s\n", g_player_name);
                    start_play_stage(queue);
                    changed = true;                  // Ÿ��Ʋ �緻��
                }
                else if (point_in_button(mx, my, &g_btn_rank)) {
                    g_scene_screne = SCENE_RANK;
                    changed = true;
                }
            }
            // 3) �����Է�: ���ͷ� ����
            else { // ALLEGRO_EVENT_KEY_CHAR
                int key = event.keyboard.keycode;
                if (key == ALLEGRO_KEY_ENTER || key == ALLEGRO_KEY_PAD_ENTER) {
                    handle_start_from_title(queue);  // �� ���� ó��
                    printf("%s\n", g_player_name);
                    start_play_stage(queue);
                    changed = true;
                }
            }

            if (changed) {
                if (g_scene_screne == SCENE_TITLE)      draw_title_screen();
                else if (g_scene_screne == SCENE_RANK)  draw_rank_screen();
                al_flip_display();
            }
        } break;


        case ALLEGRO_EVENT_KEY_DOWN: {
            int k = event.keyboard.keycode;
            switch (k) {
            case ALLEGRO_KEY_ESCAPE:
                if (g_scene_screne == SCENE_TITLE) {
                    is_done = true;
                }
                else {
                    g_scene_screne = SCENE_TITLE;
                    draw_title_screen();
                    al_flip_display();
                }
                break;
            default: break;
            }
        } break;

        default:
            break;
        }
    }

    if (g_font)     al_destroy_font(g_font);
    if (g_font_btn) al_destroy_font(g_font_btn);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);
    return 0;
}
