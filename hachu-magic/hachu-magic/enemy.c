
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "audio.h"
#include "cat.h"
#include "game_manager.h"
#include "utils.h"
#include "enemy.h"
#include "game_system.h"
#include "game_manager.h"

enemy_t g_enemy_list[ENEMY_MAX_NUMBER];
//int life_by_stage[] = { 3, 5, 7 };
int life_by_stage[] = { 3,4,5,7 };

extern int stage_wave_max_number[];

extern int stage_wave_create_enemy_number[];
extern int life;
extern game_state_t gm_state;

//2025-08-31 추가
double last_wave_clear_time = 0;
bool wave_ready_to_spawn = false;
//여기까지

inline const enemy_t* get_enemy_list(void)
{
    return &g_enemy_list;
}

void DEBUG_clear_enemy(void) {
    for (int i = 0; i < 5; i++) {
        g_enemy_list[i].type = 0;
        g_enemy_list[i].pos_x = rand() % 1400;
        g_enemy_list[i].pos_y = 0;
        g_enemy_list[i].size_w = ENEMY_WIDTH[2];
        g_enemy_list[i].size_h = ENEMY_HEIGHT[2];
    }
}

void clear_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		g_enemy_list[i].is_spawned = 0;
	}
}

void spawn_wave(void)
{
    if (MAX_STAGE_NUMBER <= gm_state.current_stage)
    {
        is_game_clear(&gm_state);
        return;
    }

    for (int i = 0; i < stage_wave_create_enemy_number[gm_state.current_stage]; i++) {
        create_enemy();
    }
    gm_state.current_wave += 1;
}

//여기 2025-08-31 오늘 추가함

void spawn_enemy() {
    double wait_time = 2.0;
    if (!is_enemy_cleared()) {
        wave_ready_to_spawn = false;  // 적이 남아있으면 딜레이 타이머 리셋
        return;
    }

    if (!wave_ready_to_spawn) {
        last_wave_clear_time = al_get_time();  // 마지막 적이 클리어된 시간 기록
        wave_ready_to_spawn = true;
        wait_time = 2.0;
    }

    if (stage_wave_max_number[gm_state.current_stage] == gm_state.current_wave) {
        gm_state.current_wave = 0;
        gm_state.current_stage += 1;
        // 스테이지가 증가했을 때 알림 띄우기
        wait_time = 4.0;
        draw_stage_announce();
    }

    double now = al_get_time();
    if (wave_ready_to_spawn && now - last_wave_clear_time >= wait_time) {
        spawn_wave();           // 2초 딜레이 후 웨이브 호출
        wave_ready_to_spawn = false;
    }
}

///


void create_enemy(void) 
{
    enemy_t temp_enemy;

    int left_attemption = 100;
    bool is_valid_position = false;

    while (!is_valid_position && left_attemption-- > 0) {
        int side = rand() % 4;
        switch (side) {
        case 0: 
            // From outside the left side of the screen (x = -50), y position is random within the range 0 to SCREEN_H       
            temp_enemy.pos_x = -50.0;     
            temp_enemy.pos_y = rand() % SCREEN_HEIGHT;
            break;
        case 1: 
            // From outside the right side of the screen (x = SCREEN_W + 50), the y position is random within the range 0 to SCREEN_H
            temp_enemy.pos_x = SCREEN_WIDTH + 50;   
            temp_enemy.pos_y = rand() % SCREEN_HEIGHT;
            break;
        case 2: 
            // From above the top of the screen (y = -50), the x position is random within the range 0 to SCREEN_W
            temp_enemy.pos_x = rand() % SCREEN_WIDTH;  
            temp_enemy.pos_y = -50.0;
            break;
        case 3: 
            // From outside the right side of the screen (x = SCREEN_W + 50), the y position is random within the range 0 to SCREEN_H
            temp_enemy.pos_x = rand() % SCREEN_WIDTH;  
            temp_enemy.pos_y = SCREEN_HEIGHT + 50;
            break;
        }

        is_valid_position = true;
        for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
            if (!g_enemy_list[i].is_spawned) continue;

            //calculate the distance between ememy and new enemy.
            float dx = g_enemy_list[i].pos_x - temp_enemy.pos_x;          
            float dy = g_enemy_list[i].pos_y - temp_enemy.pos_x;

            //거리함수
            float dist = sqrtf(dx * dx + dy * dy);      
            //너무 가까움
            if (dist < 40.0f) {
                //vaildPosition ????? ????????
                is_valid_position = false;                 
                break;
            }
        }
    }

    int index = 0;
    while (index < ENEMY_MAX_NUMBER) {
        if (!g_enemy_list[index].is_spawned) {
            break;
        }
        index += 1;
    }

    // ENEMY_MAX_NUMBER
    if (index >= ENEMY_MAX_NUMBER) {
        return;
    }

  /*  temp_enemy.type = 0;*/
    temp_enemy.type = gm_state.current_stage;


  /*  temp_enemy.life = 4; ---> 2025-08-29 여기를 바꿈으로 해서 life 부분들도 바꿔! */
    temp_enemy.life = life_by_stage[gm_state.current_stage];
    temp_enemy.received_attack_count = 0;

    temp_enemy.size_w = ENEMY_WIDTH[temp_enemy.type];
    temp_enemy.size_h = ENEMY_HEIGHT[temp_enemy.type];

    //char pattern[] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
    //memcpy(temp_enemy.pattern, pattern, sizeof(char) * 4);
    //temp_enemy.current_pattern = DIR_UP;
    for (int i = 0; i < life_by_stage[gm_state.current_stage]; i++) {
        temp_enemy.pattern[i] = (direction_t)(1 + rand() % 4);
    }
    temp_enemy.current_pattern = temp_enemy.pattern[0];  // 처음 첫 패턴으로 설정

    temp_enemy.velocity = 1;
   
    temp_enemy.is_spawned = 1;
    temp_enemy.is_invincible = 0;
    g_enemy_list[index] = temp_enemy;
}

void move_enemy()
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        if (!g_enemy_list[i].is_spawned) continue;

        double dx = get_cat()->pos_x - g_enemy_list[i].pos_x;
        double dy = get_cat()->pos_y - g_enemy_list[i].pos_y;
        double dist = sqrt(dx * dx + dy * dy);

        if (dist == 0) {
            continue;
        }

        g_enemy_list[i].pos_x += (dx / dist) * g_enemy_list[i].velocity;
        g_enemy_list[i].pos_y += (dy / dist) * g_enemy_list[i].velocity;
    }
}

bool is_enemy_cleared(void)
{
    bool is_cleared = true;

    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        is_cleared = is_cleared && !(g_enemy_list[i].is_spawned);
    }

    return is_cleared;
}

// 플레이어와 충돌 검사
bool is_collided_with_cat(enemy_t* enemy_ptr)
{
    if (enemy_ptr == NULL) {
        return false;
    }

    double ax1 = (enemy_ptr->pos_x);
    double ay1 = (enemy_ptr->pos_y);
    double ax2 = (enemy_ptr->pos_x) + (enemy_ptr->size_w);
    double ay2 = (enemy_ptr->pos_y) + (enemy_ptr->size_h);
    double bx1 = (get_cat()->pos_x);
    double by1 = (get_cat()->pos_y);
    double bx2 = (get_cat()->pos_x) + (get_cat()->size_w);
    double by2 = (get_cat()->pos_y) + (get_cat()->size_h);

    if (ax1 > bx2) return false;
    if (ax2 < bx1) return false;
    if (ay1 > by2) return false;
    if (ay2 < by1) return false;

    return true;
}

// 충돌 처리 함수
void handle_enemy_collision(void)
{
    enemy_t* enemy_ptr = g_enemy_list;

    for (int i = 0; i < ENEMY_MAX_NUMBER; ++i, ++enemy_ptr) {
        if (!(enemy_ptr->is_spawned)) {
            continue;
        }

        cat_t* target = (cat_t*)get_cat();
        if (is_collided_with_cat(enemy_ptr)) {
            // 충돌 시 적객체 소멸
            enemy_ptr->is_spawned = 0;

            apply_damage(1);
        }
    }
}