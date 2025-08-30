
#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>
#include <math.h>

#include "game_system.h"

#define MAGIC_MAX_NUMBER 15
#define MAGIC_WIDTH 100
#define MAGIC_HEIGHT 100

typedef struct _magic {
	// 현재 마법이 유효한가
	char is_spawned;

	// 마법의 종류
	magic_type_t type;

	// 현재 x 좌표 (좌측상단 기준)
	double pos_x;

	// 현재 y 좌표 (좌측상단 기준)
	double pos_y;

	// 가로 길이
	int size_w;

	// 세로 길이
	int size_h;

	// 단위 이동 속도
	double velocity;

	// 마법이 향해 날아가는 적에 대한 포인터.
	// 사용할 때 (enemy_t*)로 캐스팅하여 사용.
	void* target_ptr;

} magic_t;

/**
 * 디버깅 용으로 마법을 먼저 소환할 때 사용
 */
void DEBUG_clear_magic(void);

/**
 * magic 배열의 is_spawned 값을 초기화합니다.
 */
void clear_magic(void);

/**
 * 비어있는 magic 슬롯에 마법의 초기값을 넣습니다.
 * @param pos_x: 마법을 생성하고자 하는 x좌표
 * @param pos_y: 마법을 생성하고자 하는 x좌표
 * @param type: 마법의 공격 타입
 * @param target: 마법의 목표(적)에 대한 포인터
 */
void create_magic(double pos_x, double pos_y, magic_type_t type, enemy_t* target);

/**
 * 타겟과의 충돌에 대해 검사합니다.
 * 충돌 대상은 마법이 가지고 있는 target(enemy_t*) 의 정보를 활용합니다.
 * @param magic_ptr: 마법 구조체의 주소값
 * @return 충돌여부 boolean
 */
bool is_collided_with_target(magic_t* magic_ptr);

/**
 * 현재 소환된 모든 마법의 충돌을 검사하고, 
 * 타겟 적과의 충돌시 충돌에 대한 처리를 수행합니다.
 */
void handle_magic_collision(void);

/**
 * 단위 프레임에 대해 활성화된 모든 마법을 이동시킵니다.
 */
void move_magic(void);

#endif /* __MAGIC_H__ */
