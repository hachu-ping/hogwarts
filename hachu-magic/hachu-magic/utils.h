#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdbool.h>

#include "game_system.h"

/**
 * 첫 번째 인자로 전달된 값의 유효성을 검사합니다. 
 * 만약 해당 값이 false (0) 이라면 description 을 출력하고 프로그램을 종료합니다.
 * @param test: 유효성 검사 조건
 * @param description : 테스트 값이 유효하지 않다면 (0이라면) 해당 메시지를 출력
 * @return void / 값이 0이라면 프로그램 종료
 */
void must_init(bool test, const char* description);

/**
 * 입력받은 키 코드를 방향 열거형으로 변환합니다. 
 * 방향키 이외의 경우 DIRECTION_NONE 값을 반환합니다.
 * @param keycode: 입력받은 키의 allegro 코드값
 * @return direction_t: 방향에 대한 enum
 */
direction_t keycode_to_direction(char keycode);

/**
 * 입력받은 방향 값을 마법 타입 열거형으로 변환합니다.
 * 방향 이외의 경우 MAGIC_TYPE_NONE 값을 반환합니다.
 * @param direction: 방향 enum 값
 * @return magic_type_t: 마법 타입에 대한 enum
 */
magic_type_t direction_to_magic_type(direction_t direction);

#endif /* __UTILS_H__ */


/**
 * A brief description. A more elaborate class description
 * @param somebool a boolean argument.
 * @return The test results
 */