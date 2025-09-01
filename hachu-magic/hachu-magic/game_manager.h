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


/**
 * 게임 시작
 */
void play_game(void);

/**
 * 게임 초기화
 */void init_game(void);

/**
 * 게임 종료 후 데이터 정리
 */
void wrap_up_game(void);

// 게임 종료 여부 판정
bool is_game_over(void);

// 게임 종료 처리 (시간 계산 및 클리어 여부 설정)
void is_game_clear(void);

/**
 * 랜덤 위치에서 적을 사방에 생성하고 적을 초기화합니다.
 */
void start_play_stage(ALLEGRO_EVENT_QUEUE* main_queue);


/**
 * 플레이어가 데미지를 받습니다.
 * @param damage: 플레이어가 받을 데미지 수치
 */
void apply_damage(int damage);

/**
 * 게임 초기화 (시작) 시 오브젝트와 관련된 데이터를 초기화합니다.
 */
void clear_data(void);

/**
 * 다음 웨이브로 전환합니다.
 */
void move_to_next_wave(void);

/**
 * 다음 스테이지로 전환합니다.
 */
void move_to_next_stage(void);

/**
 * 플레이어의 이름을 변수에 담습니다.
 */
void update_player_name(char* name, int size);

#endif /* __GAME_MANAGER_H__ */

