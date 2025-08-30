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
 * ��������Ʈ �̹����� �ҷ��� �����մϴ�.
 * �̹��� �ε� �Ǵ� �����Ʈ ������ ������ ��� ���α׷��� ����˴ϴ�.
 */
void init_sprites(void);

/**
 * draw �Լ����� Ȱ���� ȭ���� ���� �׸���, â�� ǥ���մϴ�.
 * ȭ���� �׸��� ������ ������ �����ϴ�.
 * 
 * background -> enemy -> cat -> magic -> FX
 */
void refresh_screen(void);


/**
 * ���ΰ� ����̸� ȭ�鿡 �׸��ϴ�.
 * ���ΰ� ������� ���� ���¿� ���� �ٸ� �̹����� �����ݴϴ�. 
 */
void draw_cat(void);

/**
 * ����� ȭ�鿡 �׸��ϴ�.
 * ����� Stage�� ���� �޶����ϴ�. 
 */
void draw_background(void);

/**
 * ���� Ȱ��ȭ�� ������ ȭ�鿡 �׸��ϴ�.
 * ������ g_magics ���� ���� is_spawned �� ���� �׸��ϴ�.
 */
void draw_magics(void);

/**
 * ���� Ȱ��ȭ�� ���� ȭ�鿡 �׸��ϴ�.
 * ���� g_enemies ���� ���� is_spawned �� ���� �׸��ϴ�.
 */
void draw_enemies(void);

/**
 * ȭ�� ȿ���� ȭ�鿡 �׸��ϴ�.
 */
void draw_fxs(void);


#endif /* __SPRITES_H__ */

