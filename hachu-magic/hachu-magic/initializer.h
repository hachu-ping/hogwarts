#ifndef __initializer_H__
#define __initializer_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <stdbool.h>
#include "game_system.h"

/**
 * Allegro가 동작하도록 초기화합니다.
 * 초기화 실패 시 프로그램을 종료합니다.
 */
void init_allegro(void);

/**
 * Allegro의 addon들을 초기화합니다. 
 * 초기화 실패 시 프로그램을 종료합니다.
 */
void init_addons(void);

/**
 * Allegro의 드라이버들을 설치합니다. 
 * 설치 실패 시 프로그램을 종료합니다.
 */
void install_driver(void);

/**
 * 프로그램 실행에 필요한 화면 출력 리소스를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램을 종료합니다.
 * @param int width: 프로그램 디스플레이 창의 너비
 * @param int height: 프로그램 디스플레이 창의 높이
 * @return ALLEGRO_DISPLAY* 
 */
ALLEGRO_DISPLAY* init_display(const int width, const int height);

/**
 * 프로그램 실행에 필요한 타이머를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램을 종료합니다.
 * @param double speed_secs: 타이머의 한 틱 당 시간
 * @return ALLEGRO_TIMER*
 */
ALLEGRO_TIMER* init_timer(const double speed_secs);

/**
 * 프로그램 실행에 필요한 이벤트 큐를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램을 종료합니다.
 * @return ALLEGRO_EVENT_QUEUE*
 */
ALLEGRO_EVENT_QUEUE* init_event_queue(void);

/**
 * 키보드 입력을 위한 key 배열 상태변수들 관련 초기화합니다.
 */
void init_keyboard(void);

/**
 * 프로그램 실행에 필요한 폰트를 설정합니다.
 * 해당 폰트를 사용하여 ttf 파일 등을 생성합니다.
 * 폰트 초기화 완료 후 프로그램을 실행합니다.
*/
ALLEGRO_FONT* init_builtin_font(void);


/**
 * 프로그램 실행에 필요한 기본 데이터를 초기화합니다.
 */
void init_data(void);
void textbox_init(TextBox* tb, float x, float y, float w, float h, int maxlen);

#endif /* __initializer_H__ */