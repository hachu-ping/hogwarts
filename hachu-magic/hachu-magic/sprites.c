#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "cat.h"
#include "debug.h"
#include "enemy.h"
#include "fx.h"
#include "magic.h"
#include "sprites.h"
#include "utils.h"

#include "game_manager.h"

extern int g_frames;

static sprites_t sprites;
static fonts_t fonts;

// internal 함수 선언
static ALLEGRO_BITMAP* load_bitmap(const char* file_name);
static ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h);
static ALLEGRO_FONT* load_font(const char* file_name, int size);


static ALLEGRO_BITMAP* load_bitmap(const char* file_name)
{
    ALLEGRO_BITMAP* temp = al_load_bitmap(file_name);
    must_init(temp, "load sprite");

    return temp;
}

/**
 * 스프라이트 이미지를 분할하여 반환합니다.
 * 스프라이트 시트가 없다면 게임 프로그램이 종료됩니다.
 * @param sheet: 분할할 원하는 원본 시트
 * @param x: 잘라낼려는 영역 왼쪽 모서리의 x 좌표
 * @param y: 잘라낼려는 영역 위쪽 모서리의 y 좌표
 * @param w: 잘라낼려는 스프라이트 가로 길이
 * @param h: 잘라낼려는 스프라이트 세로 길이
 * @return ALLEGRO_BITMAP*: 잘린 bitmap 의 주소
 */
static ALLEGRO_BITMAP* sprite_grab(ALLEGRO_BITMAP* sheet, int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

static ALLEGRO_FONT* load_font(const char* file_name, int size)
{
    ALLEGRO_FONT* temp = al_load_ttf_font(file_name, size, 0);
    must_init(temp, "load font");
    return temp;
}

void load_sprites(void)
{
    sprites.background[0] = load_bitmap("assets/sprites/stage01.jpg");
    sprites.background[1] = load_bitmap("assets/sprites/stage02.jpg");
    sprites.background[2] = load_bitmap("assets/sprites/stage03.jpg");
    sprites.background[3] = load_bitmap("assets/sprites/stage04.jpg");
    sprites.background[4] = load_bitmap("assets/sprites/back.png");

    sprites._cat_sheet = load_bitmap("assets/sprites/cat_sprite.png");
    sprites.cat[0] = sprite_grab(sprites._cat_sheet, SPRITE_CAT_WIDTH * 0, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);
    sprites.cat[1] = sprite_grab(sprites._cat_sheet, SPRITE_CAT_WIDTH * 1, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);
    sprites.cat[2] = sprite_grab(sprites._cat_sheet, SPRITE_CAT_WIDTH * 2, 0, SPRITE_CAT_WIDTH, SPRITE_CAT_HEIGHT);

    sprites._enemy_sheet = load_bitmap("assets/sprites/enemy_sprite.png");
    sprites.enemies[0][0] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 0, 0, SPRITE_ENEMY_WIDTH[0], SPRITE_ENEMY_HEIGHT[0]);
    sprites.enemies[0][1] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 1, 0, SPRITE_ENEMY_WIDTH[0], SPRITE_ENEMY_HEIGHT[0]);
    sprites.enemies[1][0] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 2 + SPRITE_ENEMY_WIDTH[1] * 0, 0, SPRITE_ENEMY_WIDTH[1], SPRITE_ENEMY_HEIGHT[1]);
    sprites.enemies[1][1] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[0] * 2 + SPRITE_ENEMY_WIDTH[1] * 1, 0, SPRITE_ENEMY_WIDTH[1], SPRITE_ENEMY_HEIGHT[1]);
    sprites.enemies[2][0] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[2] * 0, SPRITE_ENEMY_HEIGHT[1], SPRITE_ENEMY_WIDTH[2], SPRITE_ENEMY_HEIGHT[2]);
    sprites.enemies[2][1] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[2] * 1, SPRITE_ENEMY_HEIGHT[1], SPRITE_ENEMY_WIDTH[2], SPRITE_ENEMY_HEIGHT[2]);
    sprites.enemies[3][0] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[3] * 0, SPRITE_ENEMY_HEIGHT[1] + SPRITE_ENEMY_HEIGHT[2], SPRITE_ENEMY_WIDTH[3], SPRITE_ENEMY_HEIGHT[3]);
    sprites.enemies[3][1] = sprite_grab(sprites._enemy_sheet, SPRITE_ENEMY_WIDTH[3] * 1, SPRITE_ENEMY_HEIGHT[1] + SPRITE_ENEMY_HEIGHT[2], SPRITE_ENEMY_WIDTH[3], SPRITE_ENEMY_HEIGHT[3]);

    sprites._effect_sheet = load_bitmap("assets/sprites/effect_sprite.png");
    sprites.arrows[1] = sprite_grab(sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 0, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    sprites.arrows[2] = sprite_grab(sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 1, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    sprites.arrows[3] = sprite_grab(sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 2, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    sprites.arrows[4] = sprite_grab(sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 3, SPRITE_ARROW_WIDTH, SPRITE_ARROW_HEIGHT);
    sprites.life = sprite_grab(sprites._effect_sheet, 0, SPRITE_ARROW_HEIGHT * 4, SPRITE_LIFE_WIDTH, SPRITE_LIFE_HEIGHT);
    sprites.magics[1][0] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[1][1] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[1][2] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[2][0] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[2][1] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[2][2] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[3][0] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[3][1] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[3][2] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[4][0] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 0, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[4][1] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 1, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.magics[4][2] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + MAGIC_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 2, MAGIC_WIDTH, SPRITE_MAGIC_HEIGHT);
    sprites.explosion[0] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 0, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    sprites.explosion[1] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 1, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    sprites.explosion[2] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 2, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
    sprites.explosion[3] = sprite_grab(sprites._effect_sheet, SPRITE_ARROW_WIDTH + SPRITE_EXPLOSION_WIDTH * 3, SPRITE_MAGIC_HEIGHT * 3, SPRITE_EXPLOSION_WIDTH, SPRITE_EXPLOSION_HEIGHT);
}

void load_fonts(void)
{
    fonts.font = load_font("assets/fonts/DotGothic16-Regular.ttf", FONT_DEFAULT_SIZE);
    fonts.font_title = load_font("assets/fonts/DotGothic16-Regular.ttf", FONT_TITLE_SIZE);
    fonts.font_hud = load_font("assets/fonts/DotGothic16-Regular.ttf", FONT_HUD_SIZE);
    fonts.font_stage = load_font("assets/fonts/DotGothic16-Regular.ttf", FONT_STAGE_SIZE);
}

void draw_background(int current_stage)
{
    al_draw_scaled_bitmap(sprites.background[current_stage], 0, 0, SPRITE_BACK_WIDTH[current_stage], SPRITE_BACK_HEIGHT[current_stage], 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
}

void draw_cat(double pos_x, double pos_y, double size_w, double size_h)
{
    int x_offset = (size_w - SPRITE_CAT_WIDTH) * 0.5;
    int y_offset = (size_h - SPRITE_CAT_HEIGHT) * 0.5;

    al_draw_bitmap(
        sprites.cat[g_frames / 12 % SPRITE_CAT_FRAME_NUMBER],
        pos_x + x_offset,
        pos_y + y_offset,
        0
    );

#ifdef DEBUG_MODE
    // 충돌 영역 표시
    al_draw_rectangle(pos_x, pos_y, pos_x + size_w, pos_y +size_h, al_map_rgb(0, 255, 0), 3);
#endif
}

void draw_enemy(double pos_x, double pos_y, int size_w, int size_h, int type)
{
    int x_offset = (size_w - SPRITE_ENEMY_WIDTH[type]) * 0.5;
    int y_offset = (size_h - SPRITE_ENEMY_HEIGHT[type]) * 0.5;

    al_draw_bitmap(
        sprites.enemies[type][g_frames / 16 % SPRITE_ENEMY_FRAME_NUMBER],
        pos_x + x_offset,
        pos_y + y_offset,
        0
    );
#ifdef DEBUG_MODE
    // 충돌 영역 표시
    al_draw_rectangle(pos_x, pos_y, pos_x + size_w, pos_y + size_h, al_map_rgb(255, 0, 0), 3);
#endif
}

void draw_enemy_arrow(double pos_x, double pos_y, int size_w, int size_h, int type, const char* pattern, int max_life, int damaged_amount)
{

    for (int i = damaged_amount; i < max_life; ++i) {
    double arrow_pos_x_offset = 0.5 * size_w + (-0.5 * (max_life - damaged_amount)) * SPRITE_ARROW_WIDTH + (i-damaged_amount) * SPRITE_ARROW_WIDTH;
    double arrow_pos_y_offset = (size_h - SPRITE_ENEMY_HEIGHT[type]) * 0.5 - (SPRITE_ARROW_HEIGHT * 0.8);
        al_draw_bitmap(
            sprites.arrows[pattern[i]],
            pos_x + arrow_pos_x_offset,// + i * SPRITE_ARROW_WIDTH,
            pos_y + arrow_pos_y_offset,
            0
        );
    }
}

void draw_magic(double pos_x, double pos_y, int size_w, int size_h, int type)
{
    al_draw_bitmap(
        sprites.magics[type][g_frames / 16 % SPRITE_MAGIC_FRAME_NUMBER],
        pos_x,
        pos_y,
        0
    );

#ifdef DEBUG_MODE
    // 충돌 영역 표시
    al_draw_rectangle(pos_x, pos_y,pos_x + size_w,pos_y + size_h, al_map_rgb(0, 0, 255), 3);
#endif
}

void draw_fxs(int pos_x, int pos_y, int current_frame)
{
    al_draw_bitmap(
        sprites.explosion[current_frame / SPRITE_EXPLOSION_FRAME_NUMBER],
        pos_x,
        pos_y,
        0
    );
}

//button_t g_btn_start = { 550, 380, 300, 60, "start" };
//button_t g_btn_rank = { 550, 460, 300, 60, "rank" };


// 그리기 (블링킹 커서의 타이밍용)
void draw_textbox(const text_box_t* tb) {
    // 박스 배경/테두리
    ALLEGRO_COLOR bg = tb->focused ? al_map_rgb(35, 40, 55) : al_map_rgb(28, 30, 40);
    ALLEGRO_COLOR brd = tb->focused ? al_map_rgb(90, 150, 255) : al_map_rgb(80, 80, 90);
    al_draw_filled_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, bg);
    al_draw_rectangle(tb->x, tb->y, tb->x + tb->w, tb->y + tb->h, brd, 2.0f);

    // 텍스트(빈칸 패딩)
    float pad = 10.0f;
    al_draw_text(fonts.font, al_map_rgb(255, 255, 255), tb->x + pad, tb->y + (tb->h - al_get_font_line_height(fonts.font)) / 2.0f, 0, tb->text[0] ? tb->text : "player name");

    // 커서 블링킹 (0.5초 주기)
    if (tb->focused) {
        bool on = ((int)(al_get_time() * 2.0)) % 2 == 0;
        if (on) {
            // 텍스트 너비 계산해서 커서 위치 구함
            float tw = al_get_text_width(fonts.font, tb->text);
            float cx = tb->x + pad + tw + 2.0f;
            float cy1 = tb->y + 8.0f, cy2 = tb->y + tb->h - 8.0f;
            al_draw_line(cx, cy1, cx, cy2, al_map_rgb(255, 255, 255), 1.0f);
        }
    }
}

// 버튼 안에 텍스트를 정확히 가운데 정렬해서 그려주는 유틸
void draw_button(button_t* btn, ALLEGRO_COLOR fill, ALLEGRO_COLOR textc, float border_px)
{
    // 1) 버튼 박스
    al_draw_filled_rectangle(btn->x, btn->y, btn->x + btn->w, btn->y + btn->h, fill);
    if (border_px > 0.0f) {
        al_draw_rectangle(btn->x, btn->y, btn->x + btn->w, btn->y + btn->h, al_map_rgb(255, 255, 255), border_px);
    }
    //al_clear_to_color(al_map_rgb(20, 20, 25));
    //textbox_draw(&g_name_box, fonts.font);
    //al_draw_text(fonts.font, al_map_rgb(255, 255, 255), 700, 250, ALLEGRO_ALIGN_CENTRE, "CAT vs MICE");

    // 2) 문자열 크기
    int tw = al_get_text_width(fonts.font, btn->label);
    int th = al_get_font_line_height(fonts.font);

    // 3) 가운데 좌표(가로/세로)
    float tx = btn->x + (btn->w - tw) * 0.5f;
    float ty = btn->y + (btn->h - th) * 0.5f;

    // 4) 텍스트
    al_draw_text(fonts.font, textc, tx, ty, 0, btn->label);
}

void draw_text(float pos_x, float pos_y, const char* string)
{
    al_draw_text(fonts.font, al_map_rgb(255, 255, 255), pos_x, pos_y, ALLEGRO_ALIGN_CENTRE, string);
}

void draw_text_color(float pos_x, float pos_y, const char* string, ALLEGRO_COLOR color)
{
    al_draw_text(fonts.font, color, pos_x, pos_y, ALLEGRO_ALIGN_CENTRE, string);
}

void draw_hud_text(float pos_x, float pos_y, const char* string)
{
    al_draw_text(fonts.font_hud, al_map_rgb(255, 255, 255), pos_x, pos_y, 20, string);
}

void draw_stage_text(float pos_x, float pos_y, const char* string)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));  // 화면 잠깐 비우기
    al_draw_textf(fonts.font_stage, al_map_rgb(255, 200, 200), 700, 350, ALLEGRO_ALIGN_CENTER,string);
}