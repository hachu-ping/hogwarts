#ifndef __CAT_H__
#define __CAT_H__

#include "enemy.h"

#define CAT_SIZE_W 130
#define CAT_SIZE_H 130
#define DEFAULT_ATTACK_COOLDOWN_TIME 0.2

typedef struct _cat {
	// 고양이 x 좌표 (중심점 기준)
	double pos_x;

	// 고양이 y 좌표 (중심점 기준)
	double pos_y;

	// 고양이 너비
	int size_w;

	// 고양이 높이
	int size_h;

	// 고양이 최근에 공격한 마지막 시간
	double last_attack_time;

	// 고양이 공격간격 기다려야 하는 최소 시간
	double attack_cooldown_time;
} cat_t;

/*
 * 디버깅용 고양이 생성을 위한 초기화.
 */
void DEBUG_init_cat(void);

/**
 * 고양이를 초기 초기화합니다.
 */
void init_cat(void);

/**
 * 고양이가 매프레임 할 수 있는 내용들 업데이트합니다.
 * 플레이어 이동기능 및 키 입력이 있다면 고양이 위치 업데이트 처리와 공격 행동 가능성을 처리합니다.
 */
void update_cat();


/**
 * 방향 입력에 따라, 
 * 해당 입력 방향에 맞는 마법 종류 중 가장 앞에 있는 유효한 적에게 마법을 발사하는
 * 인터페이스 함수를 수행합니다.
 * @param magic_type 입력에 따른 마법을 입력받습니다.
 */
void cast_magic(direction);

#endif /* __CAT_H__ */

