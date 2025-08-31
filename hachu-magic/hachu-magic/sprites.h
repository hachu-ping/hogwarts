#ifndef __SPRITES_H__
#define __SPRITES_H__

#include <allegro5/bitmap.h>

#define SPRITE_CAT_FRAME_NUMBER 3
#define SPRITE_CAT_ACTION_NUMBER 2

#define SPRITE_CAT_WIDTH 200
#define SPRITE_CAT_HEIGHT 200

static const int SPRITE_ENEMY_WIDTH[] = { 140, 180, 220, 320 };
static const int SPRITE_ENEMY_HEIGHT[] = { 140, 180, 220, 320 };

#define SPRITE_ENEMY_TYPE_NUMBER 4
#define SPRITE_ENEMY_FRAME_NUMBER 2

#define SPRITE_ARROW_WIDTH 80
#define SPRITE_ARROW_HEIGHT 80
#define SPRITE_ARROW_NUMBER 5

#define SPRITE_MAGIC_WIDTH 100
#define SPRITE_MAGIC_HEIGHT 100
#define SPRITE_MAGIC_TYPE_NUMBER 5
#define SPRITE_MAGIC_FRAME_NUMBER 3

#define SPRITE_LIFE_WIDTH 80
#define SPRITE_LIFE_HEIGHT 80

#define SPRITE_EXPLOSION_WIDTH 100
#define SPRITE_EXPLOSION_HEIGHT 100
#define SPRITE_EXPLOSION_FRAME_NUMBER 4


#define BACKGROUND_NUMBER 3

typedef struct _sprites
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* _cat_sheet;
    ALLEGRO_BITMAP* _enemy_sheet;
    ALLEGRO_BITMAP* _effect_sheet;


    // background
    ALLEGRO_BITMAP* background[BACKGROUND_NUMBER];

    // cat
    ALLEGRO_BITMAP* cat[SPRITE_CAT_FRAME_NUMBER];

    // arrow
    ALLEGRO_BITMAP* arrows[SPRITE_ARROW_NUMBER];

    // magic
    ALLEGRO_BITMAP* magics[SPRITE_MAGIC_TYPE_NUMBER][SPRITE_MAGIC_FRAME_NUMBER];

    // enemy
    ALLEGRO_BITMAP* enemies[SPRITE_ENEMY_TYPE_NUMBER][SPRITE_ENEMY_FRAME_NUMBER];

    // FX
    ALLEGRO_BITMAP* explosion[SPRITE_EXPLOSION_FRAME_NUMBER];
    ALLEGRO_BITMAP* life;

} sprites_t;

/**
 * 스프라이트 이미지를 불러와 저장합니다.
 * 이미지 로드 또는 스프라이트 생성에 실패할 경우 프로그램을 종료합니다.
 */
void init_sprites(void);

/**
 * draw 함수들을 활용해 화면에 그릴 그림들을 창에 표시합니다.
 * 화면에 그려질 순서는 다음과 같습니다.
 * 
 * background -> enemy -> cat -> magic -> FX
 */
void refresh_screen(void);


/**
 * 플레이어 고양이를 화면에 그립니다.
 * 플레이어 고양이의 현재 상태에 따라 다른 이미지를 출력합니다. 
 */
void draw_cat(void);

/**
 * 배경을 화면에 그립니다.
 * 배경은 Stage에 따라 달라집니다. 
 */
void draw_background(void);

/**
 * 현재 활성화된 마법을 화면에 그립니다.
 * 마법은 g_magics 배열 중에서 is_spawned 인 것만 그립니다.
 */
void draw_magics(void);

/**
 * 현재 활성화된 적을 화면에 그립니다.
 * 적은 g_enemies 배열 중에서 is_spawned 인 것만 그립니다.
 */
void draw_enemies(void);

/**
 * 화면 효과를 화면에 그립니다.
 */
void draw_fxs(void);


#endif /* __SPRITES_H__ */