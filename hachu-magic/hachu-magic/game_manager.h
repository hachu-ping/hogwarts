#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

#include "game_system.h"


#define MAX_STAGE_NUMBER 4

// 게임 상태 구조체
typedef struct _game_state {
    char player_name[MAX_NAME_LEN];
    int current_stage;
    int current_wave;
    int g_cat_life;
    double gm_start_time;
    double gm_end_time;
    bool game_clear;
    bool game_over;
    double time_taken;
} game_state_t;

extern inline const game_state_t* get_game_state(void);



void play_game(void);

// 게임 상태 초기화
void init_game(game_state_t*);

// 게임 종료 여부 판정
bool is_game_over();

// 게임 종료 처리 (시간 계산 및 클리어 여부 설정)
void is_game_clear();


void start_play_stage(ALLEGRO_EVENT_QUEUE* main_queue);


/**
 * A brief description. A more elaborate class description
 * 플레이어가 데미지를 받습니다.
 * @params damage: 플레이어가 받을 데미지 수치
 */
void apply_damage(int damage);
void clear_data(void);
void move_to_next_wave(void);
void move_to_next_stage(void);
void update_player_name(char* name, int size);

#endif /* __GAME_MANAGER_H__ */

