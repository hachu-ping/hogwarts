#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "initializer.h"
#include "magic.h"
#include "sprites.h"
#include "game_system.h"

//���� �� ����
int max_stage_number = 2;
int current_stage = 0;

int stage_wave_max_number[] = { 2, 3, 4 };
int current_wave = 0;

int stage_wave_spawn_enemy_number[] = { 5, 6, 7 };

int g_frames = 0;

char g_player_name[64] = { 0 };


//�Լ� �� ����
void clear_data(void)
{
    current_stage = 0;
    current_wave = 0;

#if __DEBUG_MODE__
    DEBUG_clear_cat();
    DEBUG_clear_enemy();
    DEBUG_clear_magic();
#else
    clear_cat();
    clear_enemy();
    clear_magic();
#endif	
}

void play_game(void)
{
    clear_data();

    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();

    // �� ���÷��� �ҽ��� ����ؾ� DISPLAY_CLOSE�� �޽��ϴ�.
    ALLEGRO_DISPLAY* disp = al_get_current_display();
    al_register_event_source(queue, al_get_display_event_source(disp));

    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());

    al_start_timer(timer);

    bool is_game_over = false;
    bool redraw = true;   // ù ������ ���� ����

    while (!is_game_over) {
        g_frames++;

        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);
        keyboard_update(&ev);

        switch (ev.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            is_game_over = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                is_game_over = true;
            }
            break;

        case ALLEGRO_EVENT_TIMER:
            // === ������Ʈ ===
            update_cat();
            spawn_wave();
            move_magic();
            move_enemy();
            handle_magic_collision();

            redraw = true;       // �� ƽ���� �� �� �׸���
            break;
        }

        // === ���� ===
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            refresh_screen();
        }
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}

extern void play_game(void);

void start_play_stage(ALLEGRO_EVENT_QUEUE* main_queue)
{
    // ���� �� ����(���ϸ� ���� �� ���)
    Scene prev = g_scene_screne;

    g_scene_screne = SCENE_PLAY;

    if (main_queue) al_pause_event_queue(main_queue, true);
    play_game();
    if (main_queue) {
        al_pause_event_queue(main_queue, false);
        al_flush_event_queue(main_queue);
    }

    g_scene_screne = SCENE_TITLE;
}
int life = 5;

void apply_damage(int damage)
{
	life -= damage;

	DEBUG_PRINT("�浹 �߻� life -> %d\n", life);

	if (life <= 0) {
		// TODO: ���ӿ��� ó���ϱ�
		DEBUG_PRINT("���� ����\n");
	}
}