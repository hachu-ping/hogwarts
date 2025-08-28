#ifndef __SPRITES_H__
#define __SPRITES_H__

#include <allegro5/bitmap.h>

#define CAT_FRAME_NUMBER 3
#define CAT_ACTION_NUMBER 2

#define CAT_WIDTH 200
#define CAT_HEIGHT 200

static const int ENEMY_WIDTH[] = { 140, 180, 220, 320 };
static const int ENEMY_HEIGHT[] = { 140, 180, 220, 320 };

#define ENEMY0_FRAME_NUMBER 2
#define ENEMY1_FRAME_NUMBER 2
#define ENEMY2_FRAME_NUMBER 2
#define ENEMY3_FRAME_NUMBER 2

#define ARROW_WIDTH 80
#define ARROW_HEIGHT 80
#define ARROW_NUMBER 4

#define MAGIC_WIDTH 80
#define MAGIC_HEIGHT 80
#define MAGIC_TYPE_NUMBER 4
#define MAGIC_EFFECT_NUMBER 3

#define EXPLOSION_NUMBER 4

#define BACKGROUND_NUMBER 3

typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* _cat_sheet;
    ALLEGRO_BITMAP* _enemy_sheet;
    ALLEGRO_BITMAP* _effect_sheet;


    // background
    ALLEGRO_BITMAP* background[BACKGROUND_NUMBER];

    // cat
    ALLEGRO_BITMAP* cat[CAT_FRAME_NUMBER];

    // arrow
    ALLEGRO_BITMAP* arrows[ARROW_NUMBER];

    // magic
    ALLEGRO_BITMAP* magics[MAGIC_TYPE_NUMBER][MAGIC_EFFECT_NUMBER];


    // enemy
    ALLEGRO_BITMAP* enemy0[ENEMY0_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy1[ENEMY1_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy2[ENEMY3_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy3[ENEMY3_FRAME_NUMBER];

    // FX
    ALLEGRO_BITMAP* explosion[EXPLOSION_NUMBER];
    ALLEGRO_BITMAP* life;

} SPRITES;

/**
 * 스프라이트 이미지를 불러와 가공합니다.
 * 이미지 로드 또는 서브비트 가공에 실패할 경우 프로그램이 종료됩니다.
 */
void init_sprites(void);

/**
 * draw 함수들을 활용해 화면을 새로 그리고, 창에 표시합니다.
 * 화면을 그리는 순서는 다음과 같습니다.
 * 
 * background -> enemy -> cat -> magic -> FX
 */
void refresh_screen(void);


/**
 * 주인공 고양이를 화면에 그립니다.
 * 주인공 고양이의 현재 상태에 따라 다른 이미지를 보여줍니다. 
 */
void draw_cat(void);

/**
 * 배경을 화면에 그립니다.
 * 배경은 Stage에 따라 달라집니다. 
 */
void draw_background(void);

/**
 * 현재 활성화된 마법을 화면에 그립니다.
 * 마법은 g_magics 에서 현재 is_spawned 인 값만 그립니다.
 */
void draw_magics(void);

/**
 * 현재 활성화된 적을 화면에 그립니다.
 * 적은 g_enemies 에서 현재 is_spawned 인 값만 그립니다.
 */
void draw_enemies(void);

/**
 * 화면 효과를 화면에 그립니다.
 */
void draw_fxs(void);


#endif /* __SPRITES_H__ */

