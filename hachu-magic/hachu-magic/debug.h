#ifndef __DEBUG_H__
#define __DEBUG_H__

// 디버그 모드를 비활성화를 원한다면 아래라인을 주석처리 해주세요.
//#define DEBUG_MODE
// 디버그 모드를 활성화를 원한다면 위라인을 주석처리 해주세요.

#ifdef DEBUG_MODE

/**
 * 개발 중 디버깅 정보 출력 printf 입니다.
 * debug.h 헤더에 #define DEBUG_MODE 가 활성화 되어있다면 
 * 정보를 출력해 줍니다.
 * 비활성화(주석처리)되어있다면 아무것도 하지 않습니다.
 * @param printf와 동일하게 인자를 전달받습니다.
 */
#define DEBUG_PRINT(fmt, ...) \
	do { \
		printf(fmt, ##__VA_ARGS__); \
	} while(0)
#else
	#define DEBUG_PRINT(fmt, ...) 
#endif /* DEBUG_ON */

#endif /* __DEBUG_H__ */