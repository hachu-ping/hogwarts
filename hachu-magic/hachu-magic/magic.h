#ifndef __MAGIC_H__
#define __MAGIC_H__

#include <stdbool.h>

#define MAGIC_MAX_NUMBER 15

typedef struct _magic {
	// 유효한 데이터인가
	char used;

	// TODO: change into enum (char)
	// 마법의 종류 (패턴)
	char type;

	// 현재 마법 탄환의 x좌표 (중앙 좌표)
	int pos_x;

	// 현재 마법 탄환의 y좌표 (중앙 좌표)
	int pos_y;

	// 마법 탄환의 가로 길이
	int size_w;

	// 마법 탄환의 세로 길이
	int size_h;

	// 마법 탄환의 이동속도
	float velocity;

	// 타겟(적)의 주소값. 사용 시 (enemy_t* 로 캐스팅하여 사용)
	void* target_ptr;

} magic_t;

/**
 * 디버깅을 위한 마법탄환 목록 초기화
 */
void DEBUG_init_magic(void);

#endif /* __MAGIC_H__ */
