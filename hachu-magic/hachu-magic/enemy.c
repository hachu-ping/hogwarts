

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "enemy.h"
#include "utils.h"
#include "cat.h"
// TODO: define max enemy number
#define MAX_ENEMY 15
enemy_t g_enemy_list[MAX_ENEMY];


void DEBUG_init_enemy(void) {
    for (int i = 0; i < 5; i++) {
        g_enemy_list[i].type = 0;
        g_enemy_list[i].pos_x = 0;
        g_enemy_list[i].pos_y = 0;
        g_enemy_list[i].size_w = 0;
        g_enemy_list[i].size_h = 0;

        // 각 적마다 다른 패턴 설정
        switch (i) {
        case 0: {
            char pattern[] = { DIR_LEFT, DIR_LEFT, DIR_RIGHT, DIR_UP }; // 1 1 2 3
            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
            g_enemy_list[i].life = sizeof(pattern);
            break;
        }
        case 1: {
            char pattern[] = { DIR_RIGHT, DIR_UP, DIR_RIGHT, DIR_RIGHT }; // 2 3 2 2
            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
            g_enemy_list[i].life = sizeof(pattern);
            break;
        }
        case 2: {
            char pattern[] = { DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT }; // 3 1 4 2
            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
            g_enemy_list[i].life = sizeof(pattern);
            break;
        }
        case 3: {
            char pattern[] = { DIR_UP, DIR_LEFT, DIR_RIGHT, DIR_UP }; // 3 1 2 3
            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
            g_enemy_list[i].life = sizeof(pattern);
            break;
        }
        case 4: {
            char pattern[] = { DIR_DOWN, DIR_RIGHT, DIR_LEFT, DIR_UP }; // 4 2 1 3
            memcpy(g_enemy_list[i].pattern, pattern, sizeof(pattern));
            g_enemy_list[i].life = sizeof(pattern);
            break;
        }
        }

        g_enemy_list[i].is_invincible = 0;
        g_enemy_list[i].received_attack_count = 0;
        g_enemy_list[i].used = 1;
        g_enemy_list[i].velocity = 1.0;

        // 현재 기대 방향 업데이트 (디버깅용)
        g_enemy_list[i].current_pattern = g_enemy_list[i].pattern[0];

        // 디버깅 출력
        printf("[DEBUG_INIT] 적 #%d 초기화 완료 (패턴: ", i);
        for (int j = 0; j < g_enemy_list[i].life; j++) {
            printf("%d ", g_enemy_list[i].pattern[j]);
        }
        printf(")\n");
    }
}






/*
void DEBUG_init_enemy(void) {
	for (int i = 0; i < 15; i++) {
		g_enemy_list[i].type = 0;
		g_enemy_list[i].pos_x = 0;
		g_enemy_list[i].pos_y = 0;
		g_enemy_list[i].size_w = 0;
		g_enemy_list[i].size_h = 0;

		// 패턴 배열 초기화 (모두 DIR_LEFT = 1)
		char pattern[] = { DIR_LEFT, DIR_LEFT, DIR_LEFT, DIR_LEFT };
		memcpy(g_enemy_list[i].pattern, pattern, sizeof(char) * 4);

		g_enemy_list[i].is_invincible = 0;
		g_enemy_list[i].life = 3;
		g_enemy_list[i].received_attack_count = 0;
		// g_enemy_list[i].current_pattern = DIR_LEFT;  // 첫 기대 방향
		g_enemy_list[i].current_pattern = 1;
		g_enemy_list[i].used = 1;
		g_enemy_list[i].velocity = 1.0;
	}
}
*/












/*
void DEBUG_init_enemy(void) {
	for (int i = 0; i < 15; i++) {
		//char* temp_pattern = calloc(20, sizeof(char));
		//memset(temp_pattern, "12340" , 3);
		g_enemy_list[i].type = 0;
		g_enemy_list[i].pos_x = 0;
		g_enemy_list[i].pos_y= 0;
		g_enemy_list[i].size_w = 0;
		g_enemy_list[i].size_h = 0;
		//memcpy(g_enemy_list[i].pattern, temp_pattern, sizeof(char) * 4);
		memcpy(g_enemy_list[i].pattern, "12340", sizeof(char) * 4);
		g_enemy_list[i].is_invincible = 0;
		g_enemy_list[i].life = 3;
		g_enemy_list[i].received_attack_count = 0;  // 0에서 수정
		g_enemy_list[i].current_pattern = 1;
		g_enemy_list[i].used = 1;
		g_enemy_list[i].velocity = 1.0;
	}
}
*/

