#ifndef __CAT_H__
#define __CAT_H__

#include "enemy.h"

#define CAT_SIZE_W 200
#define CAT_SIZE_H 200

typedef struct _cat {
	// 현재 x 좌표 (좌측상단 기준)
	int pos_x;

	// 현재 y 좌표 (좌측상단 기준)
	int pos_y;

	// 가로 길이
	int size_w;

	// 세로 길이
	int size_h;

	// 가장 최근에 공격을 한 시간
	double last_attack_time;

	// 다음 공격까지 걸리는 최소 시간
	double attack_cooldown_time;
} cat_t;

/*
 * 디버깅을 위한 고양이 값 초기화.
 */
void DEBUG_init_cat(void);

/**
 * 고양이의 값을 초기화합니다.
 */
void init_cat(void);

/**
 * 고양이의 프레임 별 동작을 정의합니다.
 * 공격이 가능할 때 키 입력이 있다면 적을 향해 마법을 사용합니다.
 */
void update_cat();


/**
 * 현재 입력에 대해, 
 * 이 입력 방향이 남은 패턴 중 가장 앞에 있는 유효한 적들을 대상으로
 * 마법을 생성합니다.
 * @param magic_type 입력에 따른 방향을 입력받습니다.
 */
void cast_magic(direction);

#endif /* __CAT_H__ */

