
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

void DEBUG_init_cat(void)
{
    g_cat.size_w = CAT_SIZE_W;
    g_cat.size_h = CAT_SIZE_H;
    g_cat.pos_x = 500;
    g_cat.pos_y = 500;
    g_cat.last_attack_time = al_get_time();
    g_cat.attack_cooldown_time = 0.2;
}

void init_cat()
{
    // 고양이의 위치
    g_cat.pos_x = 700;
    g_cat.pos_y = 400;

    // 고양이의 너비와 높이
    g_cat.size_w = CAT_SIZE_W;
    g_cat.size_h = CAT_SIZE_H;

    // 현재 시간으로 초기화 
    g_cat.last_attack_time = al_get_time();  
    g_cat.attack_cooldown_time = 0.2;
}

void update_cat()
{
    double now = al_get_time();

    // 공격 쿨타임 체크 (마지막으로 공격한 시간으로부터 충분히 지났는가)
    if (now - g_cat.last_attack_time >= g_cat.attack_cooldown_time) {
        DEBUG_PRINT("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, g_cat.last_attack_time, now - g_cat.last_attack_time);

        char left    = (g_key[ALLEGRO_KEY_LEFT]  == KEY_DOWN) ? 1 : 0;
        char right   = (g_key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        char up      = (g_key[ALLEGRO_KEY_UP]    == KEY_DOWN) ? 1 : 0;
        char down    = (g_key[ALLEGRO_KEY_DOWN]  == KEY_DOWN) ? 1 : 0;
        
        int total_pressed = left + right + up + down;
        
        // 오직 한 개 방향키를 눌렸을 때만 입력을 처리함
        if (total_pressed == 1) {
            //  여기서 Allegro 키코드 저장용으로 선언
            char keycode = 0;  
           
            if      (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else            keycode = ALLEGRO_KEY_DOWN;
            
            DEBUG_PRINT("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);

            // 마법 공격 함수 호출
            direction magic_type = keycode_to_direction(keycode);
            DEBUG_PRINT("input_dir(enum) = %d\n", magic_type);  // 1~4 출력 확인

            cast_magic(magic_type);

            // 마지막 공격 시간 갱신
            g_cat.last_attack_time = now;
        }
    }
}

void cast_magic(direction magic_type)
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* e = &g_enemy_list[i];

        DEBUG_PRINT("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            i, e->is_spawned, e->is_invincible, e->received_attack_count, e->life);

        // 1. 적이 활성화 되어있고
        // 2. 무적이 아니며
        if (!e->is_spawned || e->is_invincible) {
            continue;
        }
        // 3. 아직 남은 패턴이 있는 경우
        if (e->received_attack_count >= e->life) {
            continue;
        }

        // 4. 입력 방향이 현재 패턴과 일치하면
        if (e->current_pattern != magic_type) {
            continue;
        }

        // 마법 생성 (반환값 없이 호출만)
        create_magic(g_cat.pos_x, g_cat.pos_y, magic_type, e);
    }
}




