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

//�ܺ� ���� ����
extern Scene g_scene_screne ;
extern ALLEGRO_FONT* g_font;  // ���� ��Ʈ(���� TTF ����)
extern Button g_btn_start;
extern Button g_btn_rank;

/**
 * Ű���� �Է¿� ���� �������� g__key[]�� ���� �� ��ȣ�� ���� Ű������ �Է� ���θ� ������Ʈ�մϴ�.
 * @param event: ALLEGRO_EVENT* �� ���� �̺�Ʈ �Է��� �����մϴ�.
 */
void keyboard_update(ALLEGRO_EVENT* event);

void draw_title_screen(void);
void draw_rank_screen(void);

#endif /* __GAME_SYSTEM_H__ */

