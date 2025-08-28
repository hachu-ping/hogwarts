
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "cat.h"

extern cat_t g_cat;

void draw_cat(void)
{
    // 테스트용: 고양이를 사각형으로 표시 (50x50 크기)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // 빨간색

    al_draw_filled_rectangle(g_cat.pos_x, g_cat.pos_y, g_cat.pos_x + g_cat.size_w, g_cat.pos_y + g_cat.size_h, cat_color);
}
