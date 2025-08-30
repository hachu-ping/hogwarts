
#ifndef __initializer_H__
#define __initializer_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <stdbool.h>

/**
 * Allegro를 사용하도록 초기화합니다.
 * 초기화 실패 시 프로그램이 종료됩니다.
 */


void init_allegro(void);

/**
 * Allegro의 addon들을 초기화합니다. 
 * 초기화 실패 시 프로그램이 종료됩니다.
 */
void init_addons(void);

/**
 * Allegro의 드라이버들을 설치합니다. 
 * 설치 실패 시 프로그램이 종료됩니다.
 */
void install_driver(void);

/**
 * 프로그램 실행에 필요한 화면 관련 리소스를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램이 종료됩니다.
 * @param int width: 프로그램 윈도우의 가로 길이
 * @param int height: 프로그램 윈도우의 세로 길이
 * @return ALLEGRO_DISPLAY* 
 */
ALLEGRO_DISPLAY* init_display(const int width, const int height);

/**
 * 프로그램 실행에 필요한 타이머를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램이 종료됩니다.
 * @param double speed_secs: 타이머의 한 틱 당 시간
 * @return ALLEGRO_TIMER*
 */
ALLEGRO_TIMER* init_timer(const double speed_secs);

/**
 * 프로그램 실행에 필요한 이벤트 큐를 생성 및 초기화합니다.
 * 생성 및 초기화 실패 시 프로그램이 종료됩니다.
 * @return ALLEGRO_EVENT_QUEUE*
 */
ALLEGRO_EVENT_QUEUE* init_event_queue(void);

/**
 * 키보드 입력을 위한 key 배열 전역변수의 값을 초기화합니다.
 */
void init_keyboard(void);
/*
* 프로그램 실행에 필요한 폰트를 설정합니다.
* 내장 폰트를 생성하여 ttf 없이 사용 가능합니다.
* 생성 초기화 실패 시 프로그램이 종료됩니다.
*/
ALLEGRO_FONT* init_builtin_font(void);


/**
 * 프로그램 실행에 필요한 기본 데이터를 초기화합니다.
 */
void init_data(void);

#endif /* __initializer_H__ */