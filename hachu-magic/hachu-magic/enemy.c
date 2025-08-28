#include <string.h>
#include <stdio.h>
#include <math.h>

#include "cat.h"
#include "enemy.h"
#include "game_system.h"

enemy_t g_enemy_list[ENEMY_MAX_NUMBER];

extern cat_t g_cat;
extern int max_stage_number;
extern int current_stage;
extern int stage_wave_max_number[];
extern int current_wave;
extern int stage_wave_spawn_enemy_number[];

void DEBUG_init_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		if (i > 5) {
			g_enemy_list[i].is_spawned = 0;
			continue;
		}
		g_enemy_list[i].type = 0;
		g_enemy_list[i].pos_x = 0;
		g_enemy_list[i].pos_y= 0;
		g_enemy_list[i].size_w = 40;
		g_enemy_list[i].size_h = 40;
		memcpy(g_enemy_list[i].pattern, "0123", sizeof(char) * 4);
		g_enemy_list[i].is_invincible = 0;
		g_enemy_list[i].life = 4;
		g_enemy_list[i].received_attack_count = 0;
		g_enemy_list[i].current_pattern= '0';
		g_enemy_list[i].is_spawned = 1;
		g_enemy_list[i].velocity = 1.0;
	}
}

void init_enemy(void) {
	for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
		g_enemy_list[i].is_spawned = 0;
	}
}

void spawn_wave(void)
{
    bool is_cleared = is_enemy_cleared();

    if (!is_cleared) {
        return;
    }
    current_wave += 1;

    if (stage_wave_max_number[current_stage] == current_wave) {
        current_wave = 0;
        current_stage += 1;
    }

    if (max_stage_number == current_stage)
    {
        // 게임 종료
        printf("모든 소환 완료\n");
        return;
    }

    for (int i = 0; i < stage_wave_spawn_enemy_number[current_stage]; i++) {
        printf("%d %d\n", i, stage_wave_spawn_enemy_number[current_stage]);
        spawn_enemy();
    }
}


void spawn_enemy(void) 
{
    enemy_t temp_enemy;

    int left_attemption = 100;
    bool is_valid_position = false;

    while (!is_valid_position && left_attemption-- > 0) {
        int side = rand() % 4;
        switch (side) {
        case 0: 
            //화면 왼쪽 바깥쪽 (x = -50)에서 y 위치는 0 ~ SCREEN_H 범위 내에서 랜덤       
            temp_enemy.pos_x = -50.0;     
            temp_enemy.pos_y = rand() % SCREEN_HEIGHT;
            break;
        case 1: 
            //화면 오른쪽 바깥 (x = SCREEN_W + 50)에서, Y의 위치는 y 위치는 0 ~ SCREEN_H
            temp_enemy.pos_x = SCREEN_WIDTH + 50;   
            temp_enemy.pos_y = rand() % SCREEN_HEIGHT;
            break;
        case 2: 
            //화면 위쪽 바깥 (y = -50) 에서 ,X 의 위치는 0 ~ SCREEN_W
            temp_enemy.pos_x = rand() % SCREEN_WIDTH;  
            temp_enemy.pos_y = -50.0;
            break;
        case 3: 
            //화면 오른쪽 바깥 (x = SCREEN_W + 50) 에서 y 의 위치는 0 ~ SCREEN_H
            temp_enemy.pos_x = rand() % SCREEN_WIDTH;  
            temp_enemy.pos_y = SCREEN_HEIGHT + 50;
            break;
        }

        is_valid_position = true;
        for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
            if (!g_enemy_list[i].is_spawned) continue;

            //기존 외계인과 새 외계인 위치 차이 계산 (거리 계산)
            float dx = g_enemy_list[i].pos_x - temp_enemy.pos_x;          
            float dy = g_enemy_list[i].pos_y - temp_enemy.pos_x;

            //두 위치 사이릐 거리를 정확하게 비교하기 위해, sqrtf 제곱근 구하는 함수
            float dist = sqrtf(dx * dx + dy * dy);      
            //겹침 방지
            if (dist < 40.0f) {
                //vaildPosition 위치가 유요한지
                is_valid_position = false;                 
                break;
            }
        }
    }

    int index = 0;
    while (index < ENEMY_MAX_NUMBER) {
        if (!g_enemy_list[index].is_spawned) {
            break;;
        }
        index += 1;
    }

    // ENEMY_MAX_NUMBER를 모두 사용하는 경우
    if (index >= ENEMY_MAX_NUMBER) {
        return;
    }

    temp_enemy.type = 0;
    temp_enemy.life = 4;
    temp_enemy.received_attack_count = 0;

    temp_enemy.size_w = 40;
    temp_enemy.size_h = 40;
    
    memcpy(temp_enemy.pattern, "0123", sizeof(char) * 4);
    temp_enemy.current_pattern = '0';

    //temp_enemy.velocity = 1.0f + (rand() % 200) / 100.0f;
    temp_enemy.velocity = 1;
   
    temp_enemy.is_spawned = 1;
    temp_enemy.is_invincible = 0;
    g_enemy_list[index] = temp_enemy;
}

void move_enemy()
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        if (!g_enemy_list[i].is_spawned) continue;

        double dx = g_cat.pos_x - g_enemy_list[i].pos_x;
        double dy = g_cat.pos_y - g_enemy_list[i].pos_y;
        double dist = sqrt(dx * dx + dy * dy);

        printf("Enemy %d: dx=%.6f, dy=%.6f, dist=%.6f\n", i, dx, dy, dist);


        if (dist == 0) {
            continue;
        }

        g_enemy_list[i].pos_x += (dx / dist) * g_enemy_list[i].velocity;
        g_enemy_list[i].pos_y += (dy / dist) * g_enemy_list[i].velocity;

        if (dist < 10.0) {
            //g_enemy_list[i].is_spawned = false;
        }
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