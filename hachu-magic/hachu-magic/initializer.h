
#ifndef __initializer_H__
#define __initializer_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <stdbool.h>

/**
 * Allegro�� ����ϵ��� �ʱ�ȭ�մϴ�.
 * �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
 */


void init_allegro(void);

/**
 * Allegro�� addon���� �ʱ�ȭ�մϴ�. 
 * �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
 */
void init_addons(void);

/**
 * Allegro�� ����̹����� ��ġ�մϴ�. 
 * ��ġ ���� �� ���α׷��� ����˴ϴ�.
 */
void install_driver(void);

/**
 * ���α׷� ���࿡ �ʿ��� ȭ�� ���� ���ҽ��� ���� �� �ʱ�ȭ�մϴ�.
 * ���� �� �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
 * @param int width: ���α׷� �������� ���� ����
 * @param int height: ���α׷� �������� ���� ����
 * @return ALLEGRO_DISPLAY* 
 */
ALLEGRO_DISPLAY* init_display(const int width, const int height);

/**
 * ���α׷� ���࿡ �ʿ��� Ÿ�̸Ӹ� ���� �� �ʱ�ȭ�մϴ�.
 * ���� �� �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
 * @param double speed_secs: Ÿ�̸��� �� ƽ �� �ð�
 * @return ALLEGRO_TIMER*
 */
ALLEGRO_TIMER* init_timer(const double speed_secs);

/**
 * ���α׷� ���࿡ �ʿ��� �̺�Ʈ ť�� ���� �� �ʱ�ȭ�մϴ�.
 * ���� �� �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
 * @return ALLEGRO_EVENT_QUEUE*
 */
ALLEGRO_EVENT_QUEUE* init_event_queue(void);

/**
 * Ű���� �Է��� ���� key �迭 ���������� ���� �ʱ�ȭ�մϴ�.
 */
void init_keyboard(void);
/*
* ���α׷� ���࿡ �ʿ��� ��Ʈ�� �����մϴ�.
* ���� ��Ʈ�� �����Ͽ� ttf ���� ��� �����մϴ�.
* ���� �ʱ�ȭ ���� �� ���α׷��� ����˴ϴ�.
*/
ALLEGRO_FONT* init_builtin_font(void);


/**
 * ���α׷� ���࿡ �ʿ��� �⺻ �����͸� �ʱ�ȭ�մϴ�.
 */
void init_data(void);

#endif /* __initializer_H__ */