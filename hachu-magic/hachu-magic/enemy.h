

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <stdbool.h>

#define ENEMY_MAX_NUMBER 15
#define MAX_PATTERN_LENGTH 15

static const int ENEMY_WIDTH[] = { 140, 180, 220, 320 };
static const int ENEMY_HEIGHT[] = { 140, 180, 220, 320 };

typedef struct _enemy {
	// TODO: change into enum (char)
	// 적의 종류
	char type;

	// 적의 x좌표 (중심 좌표)
	double pos_x;

	// 적의 y좌표 (중심 좌표)
	double pos_y;

	// 적의 너비
	double size_w;

	// 적의 높이
	int size_h;

	// 이동속도
	float velocity;

	// 적이 가진 체력 == 마법의 개수와 같은 수치
	int life;

	// 적이 받은 공격 누적 횟수 == 최대 체력 - 현재 체력
	int received_attack_count;

	// TODO: change char type into enum
	// 적이 가진 배열. 배열 요소는 방향(마법키)값이 저장된다.
	char pattern[15];
	
	// 적이 현재 첫 번째 패턴 == pattern[received_attack_count]
	char current_pattern;

	// 적이 유효한 상태인가
	bool is_spawned;

	// 적이 무적상태 상태인가
	bool is_invincible;

} enemy_t;


extern inline const enemy_t* get_enemy_list(void);


/**
 * 디버깅용 적을 위한 리스트 초기화
 */
 void DEBUG_clear_enemy(void);

/**
 * 게임 시작시 모든 enemies 리스트를 초기화합니다.
 */
void clear_enemy(void);

/**
 * 랜덤 위치에서 적을 사방에 생성하고 적을 초기화합니다. 
 */
void create_enemy(void);

void spawn_wave(void);

/**
 * 모든 활성화된 적이 사라졌을 검사합니다. 
 * 모든 적이 사망 (비활성화 상태) 일때 true를 반환합니다.
 * @return bool: 전체 적이 비활성화 상태
 */
bool is_enemy_cleared(void);

/**
 * 특정 적이 고양이 플레이어와 충돌 여부를 검사합니다.
 * @param enemy_ptr: 충돌여부를 검사하려고 하는 적 구조체의 메모리 포인터
 * @return bool: 충돌 여부
 */
bool is_collided_with_cat(enemy_t* enemy_ptr);

/**
 * 모든 활성화된 적들이 플레이어와 충돌에 대해 검사합니다.
 * 충돌이 발생한 경우, 충돌이 발생한적에게 생명관리를 알립니다.
 */
void handle_enemy_collision(void);

#endif /* __ENEMY_H__ */
