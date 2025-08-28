#ifndef __CAT_H__
#define __CAT_H__
#include "enemy.h"
typedef struct _cat {
	// 현재 x좌표 (중앙 좌표)
	int pos_x;

	// 현재 y좌표 (중앙 좌표)
	int pos_y;

	// 가로 길이
	int size_w;

	// 세로 길이
	int size_h;

	// 공격 쿨타임 (1.0 == 1 sec), 공격 쿨타임 체크용 (초 단위 Allegro 시간)
	double last_attack_time;

} cat_t;

void handle_input_and_create_magic(int);
void create_magic(int, int, int, int, float, char, enemy_t*);
void init_cat();
void update_cat();
void draw_cat();

/*
 * 디버깅을 위한 고양이 값 초기화
 */
void DEBUG_init_cat(void);

#endif /* __CAT_H__ */

