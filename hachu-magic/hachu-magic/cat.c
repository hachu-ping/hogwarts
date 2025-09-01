
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

static cat_t g_cat;

const cat_t* get_cat()
{
    return &g_cat;
}

void clear_cat()
{
    // 고양이의 위치
    g_cat.pos_x = ((SCREEN_WIDTH - CAT_SIZE_W) / 2) + 50;
    g_cat.pos_y = ((SCREEN_HEIGHT - CAT_SIZE_H) / 2) + 50;

    // 고양이의 너비와 높이
    g_cat.size_w = CAT_SIZE_W;
    g_cat.size_h = CAT_SIZE_H;

    // 공격 시간관련 초기화 
    g_cat.last_attack_time = al_get_time();  
    g_cat.attack_cooldown_time = 0.2;
}

void update_cat()
{
    double now = al_get_time();

    // 공격 쿨타임 체크 (마지막으로 공격한 시간으로부터 충분히 지났는가)
    if (now - g_cat.last_attack_time >= g_cat.attack_cooldown_time) {
        //DEBUG_PRINT("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, g_cat.last_attack_time, now - g_cat.last_attack_time);

        char left    = (g_key[ALLEGRO_KEY_LEFT]  == KEY_DOWN) ? 1 : 0;
        char right   = (g_key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        char up      = (g_key[ALLEGRO_KEY_UP]    == KEY_DOWN) ? 1 : 0;
        char down    = (g_key[ALLEGRO_KEY_DOWN]  == KEY_DOWN) ? 1 : 0;
        
        int total_pressed = left + right + up + down;
        
        // 방향키 중 한 개 방향키가 눌려진 경우 입력을 처리함
        if (total_pressed == 1) {
            //  여기서 Allegro 키코드 알레그로로 변환
            char keycode = 0;  
           
            if      (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else            keycode = ALLEGRO_KEY_DOWN;
            
            DEBUG_PRINT("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);

            // 마법 공격 함수 호출
            direction_t direction = keycode_to_direction(keycode);
            DEBUG_PRINT("input_dir(enum) = %d\n", direction);  // 1~4 값인 확인

            cast_magic(direction);

            // 공격한 마지막 시간 업데이트
            g_cat.last_attack_time = now;
        }
    }
}

void cast_magic(direction_t direction)
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* e = get_enemy_list()+i;

        DEBUG_PRINT("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            i, e->is_spawned, e->is_invincible, e->received_attack_count, e->life);

        // 1. 적이 활성화 되어있고
        // 2. 무적이 아니면
        if (!e->is_spawned || e->is_invincible) {
            continue;
        }
        // 3. 공격 받은 횟수가 최대인 경우
        if (e->received_attack_count >= e->life) {
            continue;
        }

        // 4. 입력 방향과 현재 패턴과 일치하면
        if (e->current_pattern != (magic_type_t) direction) {
            continue;
        }

        // 마법 생성 (실환은 마법 호출만)
        create_magic(g_cat.pos_x, g_cat.pos_y, (magic_type_t) direction, e);
    }
}