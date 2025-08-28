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

#define BACKGROUND_NUMBER 3

typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* _cat_sheet;

    // background
    ALLEGRO_BITMAP* background[BACKGROUND_NUMBER];

    // cat
    ALLEGRO_BITMAP* cat[CAT_FRAME_NUMBER];
    ALLEGRO_BITMAP* life;

    // magic

    // enemy
    ALLEGRO_BITMAP* enemy0[ENEMY0_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy1[ENEMY1_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy2[ENEMY3_FRAME_NUMBER];
    ALLEGRO_BITMAP* enemy3[ENEMY3_FRAME_NUMBER];

    // FX
    //ALLEGRO_BITMAP* explosion[EXPLOSION_FRAMES];
    //ALLEGRO_BITMAP* sparks[SPARKS_FRAMES];

} SPRITES;

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

