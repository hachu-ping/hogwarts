
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <stdio.h>

#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "game_system.h"
#include "magic.h"
#include "utils.h"

#define KEY_SEEN     1
#define KEY_DOWN     2

extern unsigned char g_key[ALLEGRO_KEY_MAX];
extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

cat_t g_cat;


void clear_cat()
{
    // �������� ��ġ
    g_cat.pos_x = 700;
    g_cat.pos_y = 400;

    // �������� �ʺ�� ����
    g_cat.size_w = CAT_SIZE_W;
    g_cat.size_h = CAT_SIZE_H;

    // ���� �ð����� �ʱ�ȭ 
    g_cat.last_attack_time = al_get_time();  
    g_cat.attack_cooldown_time = 0.2;
}

void update_cat()
{
    double now = al_get_time();

    // ���� ��Ÿ�� üũ (���������� ������ �ð����κ��� ����� �����°�)
    if (now - g_cat.last_attack_time >= g_cat.attack_cooldown_time) {
        //DEBUG_PRINT("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, g_cat.last_attack_time, now - g_cat.last_attack_time);

        char left    = (g_key[ALLEGRO_KEY_LEFT]  == KEY_DOWN) ? 1 : 0;
        char right   = (g_key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        char up      = (g_key[ALLEGRO_KEY_UP]    == KEY_DOWN) ? 1 : 0;
        char down    = (g_key[ALLEGRO_KEY_DOWN]  == KEY_DOWN) ? 1 : 0;
        
        int total_pressed = left + right + up + down;
        
        // ���� �� �� ����Ű�� ������ ���� �Է��� ó����
        if (total_pressed == 1) {
            //  ���⼭ Allegro Ű�ڵ� ��������� ����
            char keycode = 0;  
           
            if      (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else            keycode = ALLEGRO_KEY_DOWN;
            
            DEBUG_PRINT("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);

            // ���� ���� �Լ� ȣ��
            direction_t direction = keycode_to_direction(keycode);
            DEBUG_PRINT("input_dir(enum) = %d\n", direction);  // 1~4 ��� Ȯ��

            cast_magic(direction);

            // ������ ���� �ð� ����
            g_cat.last_attack_time = now;
        }
    }
}

void cast_magic(direction_t direction)
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* e = &g_enemy_list[i];

        DEBUG_PRINT("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            i, e->is_spawned, e->is_invincible, e->received_attack_count, e->life);

        // 1. ���� Ȱ��ȭ �Ǿ��ְ�
        // 2. ������ �ƴϸ�
        if (!e->is_spawned || e->is_invincible) {
            continue;
        }
        // 3. ���� ���� ������ �ִ� ���
        if (e->received_attack_count >= e->life) {
            continue;
        }

        // 4. �Է� ������ ���� ���ϰ� ��ġ�ϸ�
        if (e->current_pattern != (magic_type_t) direction) {
            continue;
        }

        // ���� ���� (��ȯ�� ���� ȣ�⸸)
        create_magic(g_cat.pos_x, g_cat.pos_y, (magic_type_t) direction, e);
    }
}





void DEBUG_clear_cat(void)
{
	// TODO: Modify to valid values
	g_cat.size_w = 200;
	g_cat.size_h = 200;
	g_cat.pos_x = 500;
	g_cat.pos_y = 500;
	g_cat.last_attack_time = 0.2;
}