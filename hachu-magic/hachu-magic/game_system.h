#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "scene_manager.h"

#define KEY_SEEN     1
#define KEY_DOWN     2

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

#define MAX_RANK 10
#define MAX_NAME_LEN 20

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


#if defined(_MSC_VER)
#define STRCPY_SAFE(dst, src) strncpy_s(dst, sizeof(dst), src, _TRUNCATE)
#else
#define STRCPY_SAFE(dst, src) snprintf(dst, sizeof(dst), "%s", src)
#endif


static inline bool is_pointed_in_button(float mx, float my, button_t* b) {
    return (mx >= b->x && mx <= b->x + b->w && my >= b->y && my <= b->y + b->h);
}

// 텍스트 박스
typedef struct _text_box{
    float x, y, w, h;
    bool  focused;
    int   maxlen;
    int   len;
    char  text[64];   // 최대 63자 + '\0' (필요시 크기 조절가능)
} text_box_t;


// 함수 선언
void textbox_init(text_box_t* tb, float x, float y, float w, float h, int maxlen);
bool textbox_handle_event(text_box_t* tb, const ALLEGRO_EVENT* ev); // 변경 있으면 true

/**
 * 키보드 입력에 따라 전역변수 g__key[]에 해당 키 번호에 따른 키보드 입력 상태를 업데이트합니다.
 * @param event: ALLEGRO_EVENT* 를 매개 이벤트 입력을 받습니다.
 */
void keyboard_update(ALLEGRO_EVENT* event);
void textbox_clear(text_box_t* tb);


extern inline const rank_entry_t* get_rankings(void);
extern inline const text_box_t* get_name_box(void);

// 랭킹 엔트리
typedef struct _rank_entry {
    char name[MAX_NAME_LEN];
    float time;  // -1은 실패 표시
} rank_entry_t;


void prepare_game_start(void);

// 랭킹 관련 함수들

/**
 * 저장된 랭킹 정보를 파일에서 불러옵니다.
 */
void load_rankings(void);

/**
 * 랭킹 정보를 파일에 저장합니다.
 */
void save_rankings(void);

/**
 * 점수 구조체를 비교합니다.
 */
int compare_scores(const void*, const void*);

/**
 * 랭킹 목록에 점수를 추가합니다.
 */
void add_score(const char*, float);




#endif /* __GAME_SYSTEM_H__ */

