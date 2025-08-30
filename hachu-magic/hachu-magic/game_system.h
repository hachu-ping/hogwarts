#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define KEY_SEEN     1
#define KEY_DOWN     2

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

extern unsigned char key[ALLEGRO_KEY_MAX];

typedef enum _magic_type {
    MAGIC_TYPE_NONE   = 0,
    MAGIC_TYPE_FIRE   = 1,
    MAGIC_TYPE_WATER  = 2,
    MAGIC_TYPE_AIR    = 3,
    MAGIC_TYPE_NATURE = 4
} magic_type_t;

typedef enum _direction {
    DIRECTION_NONE  = 0,
    DIRECTION_LEFT  = 1,
    DIRECTION_RIGHT = 2,
    DIRECTION_UP    = 3,
    DIRECTION_DOWN  = 4
} direction_t;


typedef enum { SCENE_TITLE, SCENE_PLAY, SCENE_RANK } Scene;

typedef struct {
    float x, y, w, h;
    const char* label;
} Button;

static inline bool point_in_button(float mx, float my, Button* b) {
    return (mx >= b->x && mx <= b->x + b->w && my >= b->y && my <= b->y + b->h);
}

//외부 변수 선언
extern Scene g_scene_screne ;
extern ALLEGRO_FONT* g_font;  // 내장 폰트(별도 TTF 없이)
extern Button g_btn_start;
extern Button g_btn_rank;

/**
 * 키보드 입력에 따라 전역변수 g__key[]에 현재 각 기호에 대한 키보드의 입력 여부를 업데이트합니다.
 * @param event: ALLEGRO_EVENT* 를 통해 이벤트 입력을 감지합니다.
 */
void keyboard_update(ALLEGRO_EVENT* event);

void draw_title_screen(void);
void draw_rank_screen(void);

#endif /* __GAME_SYSTEM_H__ */

