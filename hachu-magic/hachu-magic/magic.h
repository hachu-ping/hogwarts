
#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>
#include <math.h>

#include "game_system.h"

#define MAGIC_MAX_NUMBER 15
#define MAGIC_WIDTH 100
#define MAGIC_HEIGHT 100

typedef struct _magic {
	// 마법 객체가 유효한가
	char is_spawned;

	// 마법의 종류
	magic_type_t type;

	// 마법 x 좌표 (중심점 기준)
	double pos_x;

	// 마법 y 좌표 (중심점 기준)
	double pos_y;

	// 마법 너비
	int size_w;

	// 마법 높이
	int size_h;

	// 마법 이동 속도
	double velocity;

	// 마법이 향할 대상객체 포인터 주소 저장값.
	// 사용시 적 (enemy_t*)로 캐스팅하여 사용.
	void* target_ptr;

} magic_t;

extern inline const magic_t* get_magic_list(void);

/**
 * 디버깅용 마법을 생성할 때 사용할 함수
 */
void DEBUG_clear_magic(void);

/**
 * magic 배열의 is_spawned 값들 초기화합니다.
 */
void clear_magic(void);

/**
 * 사용가능한 magic 슬롯에 마법의 초기값을 넣습니다.
 * @param pos_x: 마법을 생성하고자 하는 x좌표
 * @param pos_y: 마법을 생성하고자 하는 y좌표
 * @param type: 마법의 속성 타입
 * @param target: 마법의 목표(적)에 대한 포인터
 */
void create_magic(double pos_x, double pos_y, magic_type_t type, enemy_t* target);

/**
 * 타겟과의 충돌을 체크 검사합니다.
 * 충돌 발생시 마법을 가지고 있는 target(enemy_t*) 에 데미지 활성화합니다.
 * @param magic_ptr: 마법 구조체의 주소값
 * @return 충돌여부 boolean
 */
bool is_collided_with_target(magic_t* magic_ptr);

/**
 * 모든 생성된 마법 객체들 충돌을 검사하고, 
 * 타겟 객체와 충돌시 충돌에 대한 처리를 실행합니다.
 */
void handle_magic_collision(void);

/**
 * 마법 프레임마다 모든 활성화된 마법 객체들을 이동시킵니다.
 */
void move_magic(void);

#endif /* __MAGIC_H__ */
