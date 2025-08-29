
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "cat.h"
#include "utils.h"
#include "enemy.h"
#include "game_system.h"

enemy_t g_enemy_list[ENEMY_MAX_NUMBER];
//int life_by_stage[] = { 3, 5, 7 };
int life_by_stage[] = { 3,4,5,7 };

extern cat_t g_cat;
extern int max_stage_number;
extern int current_stage;
extern int stage_wave_max_number[];
extern int current_wave;
extern int stage_wave_spawn_enemy_number[];

void DEBUG_init_enemy(void) {
    for (int i = 0; i < 5; i++) {
        g_enemy_list[i].type = 0;
        g_enemy_list[i].pos_x = 0;
        g_enemy_list[i].pos_y = 0;
        g_enemy_list[i].size_w = 180;
        g_enemy_list[i].size_h = 180;
    }
}

//디버그 테스트용 enemy
//void DEBUG_init_enemy(void) {
//    for (int i = 0; i < 5; i++) {
//        g_enemy_list[i].type = 0;
//        g_enemy_list[i].pos_x = 0;
//        g_enemy_list[i].pos_y = 0;
//        g_enemy_list[i].size_w = 50;
//        g_enemy_list[i].size_h = 50;
//
//        // ?? ?????? ??? ???? ????
//        switch (i) {
//        case 0: {
//            char pattern[] = { DIR_LEFT, DIR_LEFT, DIR_RIGHT, DIR_UP }; // 1 1 2 3
//            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
//            g_enemy_list[i].life = sizeof(pattern);
//            break;
//        }
//        case 1: {
//            char pattern[] = { DIR_RIGHT, DIR_UP, DIR_RIGHT, DIR_RIGHT }; // 2 3 2 2
//            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
//            g_enemy_list[i].life = sizeof(pattern);
//            break;
//        }
//        case 2: {
//            char pattern[] = { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT }; // 3 1 4 2
//            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
//            g_enemy_list[i].life = sizeof(pattern);
//            break;
//        }
//        case 3: {
//            char pattern[] = { DIR_UP, DIR_LEFT, DIR_RIGHT, DIR_UP }; // 3 1 2 3
//            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
//            g_enemy_list[i].life = sizeof(pattern);
//            break;
//        }
//        case 4: {
//            char pattern[] = { DIR_DOWN, DIR_RIGHT, DIR_LEFT, DIR_UP }; // 4 2 1 3
//            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
//            g_enemy_list[i].life = sizeof(pattern);
//            break;
//        }
//        }
//
//        g_enemy_list[i].is_invincible = 0;
//        g_enemy_list[i].received_attack_count = 0;
//        g_enemy_list[i].is_spawned= 1;
//        g_enemy_list[i].velocity = 1.0;
//
//        // ???? ??? ???? ??????? (??????)
//        g_enemy_list[i].current_pattern = g_enemy_list[i].pattern[0];
//
//    }
//}



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


    if (stage_wave_max_number[current_stage] == current_wave) {
        current_wave = 0;
        current_stage += 1;
    }
 
 
   

    
    if (max_stage_number == current_stage)
    {
        // ???? ????
        printf("Game Over\n");
        return;
    }

    for (int i = 0; i < stage_wave_spawn_enemy_number[current_stage]; i++) {
        printf("%d %d\n", i, stage_wave_spawn_enemy_number[current_stage]);
        spawn_enemy();
    }
    current_wave += 1;
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

            //제곡근함수
            float dist = sqrtf(dx * dx + dy * dy);      
            //??ħ ????
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
            break;;
        }
        index += 1;
    }

    // ENEMY_MAX_NUMBER
    if (index >= ENEMY_MAX_NUMBER) {
        return;
    }

  /*  temp_enemy.type = 0;*/
    temp_enemy.type = current_stage;


  /*  temp_enemy.life = 4; ---> 2025-08-29 여기를 바꿔야함 밑에 life 부분으로 바꿈! */
    temp_enemy.life = life_by_stage[current_stage];
    temp_enemy.received_attack_count = 0;

    temp_enemy.size_w = 180;
    temp_enemy.size_h = 180;

    //char pattern[] = { rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1, rand() % 4 + 1 };
    //memcpy(temp_enemy.pattern, pattern, sizeof(char) * 4);
    //temp_enemy.current_pattern = DIR_UP;
    for (int i = 0; i < life_by_stage[current_stage]; i++) {
        temp_enemy.pattern[i] = (Direction)(1 + rand() % 4);
    }
    temp_enemy.current_pattern = temp_enemy.pattern[0];  // 패턴 첫 방향으로 설정

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

        //printf("Enemy %d: dx=%.6f, dy=%.6f, dist=%.6f\n", i, dx, dy, dist);


        if (dist == 0) {
            continue;
        }

        g_enemy_list[i].pos_x += (dx / dist) * g_enemy_list[i].velocity;
        g_enemy_list[i].pos_y += (dy / dist) * g_enemy_list[i].velocity;

        if (dist < 10.0) {
            // TODO: 디버깅을 위한 코드임. 
            // 이후 충돌 구현 시 제거하기
            g_enemy_list[i].is_spawned = false;
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