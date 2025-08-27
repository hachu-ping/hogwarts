#ifndef __CAT_H__
#define __CAT_H__

typedef struct _cat {
	// 현재 x좌표 (중앙 좌표)
	int pos_x;

	// 현재 y좌표 (중앙 좌표)
	int pos_y;

	// 가로 길이
	int size_w;

	// 세로 길이
	int size_h;

	// 공격 쿨타임 (1.0 == 1 sec)
	float attack_delay;

} cat_t;

/**
 * 디버깅을 위한 고양이 값 초기화
 */
void DEBUG_init_cat(void);

#endif /* __CAT_H__ */