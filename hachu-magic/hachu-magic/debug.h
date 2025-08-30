#ifndef __DEBUG_H__
#define __DEBUG_H__

// 디버그 모드의 비활성화 위해서는 아래 줄을 주석처리 해주세요.
#define DEBUG_MODE

#ifdef DEBUG_MODE

/**
 * 실행 중 디버깅을 위한 printf 입니다.
 * debug.h 파일의 #define DEBUG_MODE 이 활성화 되어있다면 
 * 전달한 내용을 출력합니다.
 * 비활성화(주석처리)되어있다면 출력하지 않습니다.
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