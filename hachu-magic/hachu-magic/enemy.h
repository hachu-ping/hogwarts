

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdbool.h>

#define ENEMY_MAX_NUMBER 15

typedef struct _enemy {
	// TODO: change into enum (char)
	// 적의 종류
	int type;

	// 현재 x좌표 (중앙 좌표)
	double pos_x;

	// 현재 y좌표 (중앙 좌표)
	double pos_y;

	// 가로 길이
	double size_w;

	// 세로 길이
	int size_h;

	// 이동속도
	float velocity;

	// 적의 최대 체력 == 패턴의 길이와 동일함
	int life;

	// 적이 현재 받은 피해량 == 최대 체력 - 남은 체력
	int received_attack_count;

	// TODO: change char type into enum
	// 적의 패턴 배열. 배열 요소는 패턴(방향키)으로 구성된다.
	char pattern[15];
	
	// 현재 남은 첫 번째 패턴 == pattern[received_attack_count]
	char current_pattern;

	// 적이 유효한 상태인가
	bool is_spawned;

	// 적이 무적인 상태인가
	bool is_invincible;

} enemy_t;

/**
 * 디버깅을 위한 적 리스트 초기화
 */
 void DEBUG_init_enemy(void);

/**
 * 적의 목록을 담는 enemies 리스트를 초기화합니다.
 */
void init_enemy(void);

void spawn_enemy(void);

bool is_enemy_cleared(void);

bool is_collided_with_cat(enemy_t* enemy_ptr);

void handle_enemy_collision();


#endif /* __ENEMY_H__ */


