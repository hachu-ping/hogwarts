
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>

#include "cat.h"
#include "enemy.h"
#include "utils.h"
#include "magic.h"
#include <allegro5/keycodes.h>
#include "game_system.h"

#include <stdio.h>

cat_t g_cat;

#define KEY_SEEN     1
#define KEY_DOWN     2

extern unsigned char g_key[ALLEGRO_KEY_MAX];
extern enemy_t g_enemy_list[ENEMY_MAX_NUMBER];
extern magic_t g_magic_list[MAGIC_MAX_NUMBER];

void init_cat()
{
    g_cat.pos_x = 700;  // 중앙
    g_cat.pos_y = 400;
    g_cat.size_w = 150;    // 고양이 너비
    g_cat.size_h = 150;    // 고양이 높이

    g_cat.last_attack_time = al_get_time();  // 현재 시간으로 초기화 
}


void update_cat()
{
    // TODO 
    /*
    // 라운드마다 고양이 위치 고정
    switch (current_round)
    {
    case 1:
        cat.x = 700;  // 중앙
        cat.y = 400;
        break;
    case 2:
        cat.x = 350;  // 왼쪽 중간
        cat.y = 400;
        break;
    case 3:
        cat.x = 1050; // 오른쪽 중간
        cat.y = 400;
        break;
    default:
        cat.x = 700;
        cat.y = 400;
        break;
    }
    */
    
    double now = al_get_time();

    // 쿨타임 체크 (0.2초 경과 여부)
    if (now - g_cat.last_attack_time >= 0.2)
        
    {
        // printf("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, cat.last_attack_time, now - cat.last_attack_time);                                                   // (KEY_DOWN | KEY_SEEN)) 
        int left = (g_key[ALLEGRO_KEY_LEFT] == KEY_DOWN) ? 1 : 0;          
        int right = (g_key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        int up = (g_key[ALLEGRO_KEY_UP] == KEY_DOWN ) ? 1 : 0;
        int down = (g_key[ALLEGRO_KEY_DOWN] == KEY_DOWN) ? 1 : 0;

        
        
        int total_pressed = left + right + up + down;
        
        // 오직 한 개 방향키만 눌렸을 때만 유효
        if (total_pressed == 1)
        {
            int keycode = 0;  //  여기서 Allegro 키코드 저장용으로 선언
           

            if (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else if (down)  keycode = ALLEGRO_KEY_DOWN;
           
            printf("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);

            // 마법 공격 함수 호출
            Direction input_dir = keycode_to_direction(keycode);
            printf("input_dir(enum) = %d\n", input_dir);  // 1~4 출력 확인

            handle_input(input_dir);

            // 마지막 공격 시간 갱신
            g_cat.last_attack_time = now;
        }
    }
}

void handle_input(int input_dir)
{
    for (int i = 0; i < ENEMY_MAX_NUMBER; i++) {
        enemy_t* e = &g_enemy_list[i];

        
        // 1. 적이 사용 중이고
        // 2. 무적이 아니며
        // 3. 아직 남은 패턴이 있고
        //printf("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            //i, e->is_spawned, e->is_invincible, e->received_attack_count, e->life);

        if (e->is_spawned && !e->is_invincible && e->received_attack_count < e->life)
        {


            char expected_dir = e->pattern[e->received_attack_count];
            
            // 4. 입력 방향이 패턴과 일치하면
            if (expected_dir == input_dir)
            {
                //printf("[MAGIC-LOGIC] 적 #%d: 패턴 일치 (%d)\n", i, input_dir);

                // 5. 마법 생성 (반환값 없이 호출만)
                create_magic(g_cat.pos_x, g_cat.pos_y, 20, 20, 10.0f, input_dir, e);

                // 6. 패턴 한 단계 진도 증가
                e->received_attack_count++;


            }
            else {
                //printf("[MAGIC-LOGIC] 적 #%d: 패턴 불일치 (입력: %d, 기대값: %d)\n", i, input_dir, e->pattern[e->received_attack_count]);
            }
        }
    }
}





void DEBUG_init_cat(void) 
{
	// TODO: Modify to valid values
	g_cat.size_w = 200;
	g_cat.size_h = 200;
	g_cat.pos_x = 500;
	g_cat.pos_y = 500;
	g_cat.last_attack_time = 0.2;
}