#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <allegro5/bitmap.h>
#include "sprites.h"

#define BACKGROUND_NUMBER 5

typedef enum _background_type {
    BACKGROUND_TYPE_ST1 = 0,
    BACKGROUND_TYPE_ST2 = 1,
    BACKGROUND_TYPE_ST3 = 2,
    BACKGROUND_TYPE_ST4 = 3,
    BACKGROUND_TYPE_START = 4
} background_type_t;

/**
 * draw 함수들을 활용해 화면에 그릴 그림들을 창에 표시합니다.
 * 화면에 그려질 순서는 다음과 같습니다.
 *
 * background -> enemy -> cat -> magic -> FX
 */
void refresh_game_screen(void);

/**
 * 플레이어 고양이를 화면에 그립니다.
 * 플레이어 고양이의 현재 상태에 따라 다른 이미지를 출력합니다.
 */
void refresh_cat(void);

/**
 * 배경을 화면에 그립니다.
 * 배경은 Stage에 따라 달라집니다.
 */
void refresh_background(void);

/**
 * 현재 활성화된 마법을 화면에 그립니다.
 * 마법은 g_magics 배열 중에서 is_spawned 인 것만 그립니다.
 */
void refresh_magics(void);

/**
 * 현재 활성화된 적을 화면에 그립니다.
 * 적은 g_enemies 배열 중에서 is_spawned 인 것만 그립니다.
 */
void refresh_enemies(void);

/**
 * 화면 효과를 화면에 그립니다.
 */
void refresh_fxs(void);


void refresh_scene(void);


#endif /* __SCREEN_H__ */