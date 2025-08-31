#ifndef __SPRITES_H__
#define __SPRITES_H__

#include <allegro5/bitmap.h>
#include "game_manager.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 800

#define SPRITE_CAT_FRAME_NUMBER 3
#define SPRITE_CAT_ACTION_NUMBER 2

#define SPRITE_CAT_WIDTH 200
#define SPRITE_CAT_HEIGHT 200

static const int SPRITE_ENEMY_WIDTH[] = { 140, 180, 220, 320 };
static const int SPRITE_ENEMY_HEIGHT[] = { 140, 180, 220, 320 };
static const int SPRITE_BACK_WIDTH[] = { 2502, 2502, 2502, 2502, 1536 };//1536, 1024
static const int SPRITE_BACK_HEIGHT[] = { 1668, 1668, 1668,1668, 1024 };

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

#define SPRITE_BACKGROUND_NUMBER 5

#define FONT_DEFAULT_SIZE 24
#define FONT_TITLE_SIZE 24
#define FONT_HUD_SIZE 35
#define FONT_STAGE_SIZE 55

typedef struct _sprites
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* _cat_sheet;
    ALLEGRO_BITMAP* _enemy_sheet;
    ALLEGRO_BITMAP* _effect_sheet;


    // background
    ALLEGRO_BITMAP* background[SPRITE_BACKGROUND_NUMBER];

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

typedef struct _fonts
{
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* font_title;
    ALLEGRO_FONT* font_hud;
    ALLEGRO_FONT* font_stage;

} fonts_t;

/**
 * 스프라이트 이미지를 불러와 저장합니다.
 * 이미지 로드 또는 스프라이트 생성에 실패할 경우 프로그램을 종료합니다.
 */
void load_sprites(void);

/**
 * 폰트를 불러와 저장합니다.
 * 폰트 로드에 실패할 경우 프로그램을 종료합니다.
 */
void load_fonts(void);

/**
 * 플레이어 고양이를 화면에 그립니다.
 * 플레이어 고양이의 현재 상태에 따라 다른 이미지를 출력합니다. 
 */
void draw_cat(double pos_x, double pos_y, double size_w, double size_h);

/**
 * 배경을 화면에 그립니다.
 * 배경은 Stage에 따라 달라집니다. 
 * @param current_stage: 그리려는 스테이지 번호
 */
void draw_background(int current_stage);

/**
 * 현재 활성화된 마법을 화면에 그립니다.
 * 마법은 g_magics 배열 중에서 is_spawned 인 것만 그립니다.
 */
void draw_magics(double pos_x, double pos_y, int size_w, int size_h, int type);

/**
 * 현재 활성화된 적을 화면에 그립니다.
 * 
 */
void draw_enemy(double pos_x, double pos_y, int size_w, int size_h, int type);

/**
 * 화면 효과를 화면에 그립니다.
 */
void draw_fxs(int pos_x, int pos_y, int current_frame);

void draw_title_screen(void);
void draw_textbox(const text_box_t* tb);
void draw_button(button_t* btn, ALLEGRO_COLOR fill, ALLEGRO_COLOR textc, float border_px);
void draw_text(float pos_x, float pos_y, const char* string);

#endif /* __SPRITES_H__ */