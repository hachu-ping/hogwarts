#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "example.h"

// from display
#define BUFFER_W 320
#define BUFFER_H 240

extern SPRITES sprites;


#define ALIEN_BUG_W      ALIEN_W[0]
#define ALIEN_BUG_H      ALIEN_H[0]
#define ALIEN_ARROW_W    ALIEN_W[1]
#define ALIEN_ARROW_H    ALIEN_H[1]
#define ALIEN_THICCBOI_W ALIEN_W[2]
#define ALIEN_THICCBOI_H ALIEN_H[2]

typedef enum ALIEN_TYPE
{
    ALIEN_TYPE_BUG = 0,
    ALIEN_TYPE_ARROW,
    ALIEN_TYPE_THICCBOI,
    ALIEN_TYPE_N
} ALIEN_TYPE;

typedef struct ALIEN
{
    int x, y;
    ALIEN_TYPE type;
    int shot_timer;
    int blink;
    int life;
    bool used;
} ALIEN;

#define ALIENS_N 16
ALIEN aliens[ALIENS_N];
extern long frames;
extern long score;

void aliens_init()
{
    for (int i = 0; i < ALIENS_N; i++)
        aliens[i].used = false;
}

void aliens_update()
{
    int new_quota =
        (frames % 120)
        ? 0
        : between(2, 4)
        ;
    int new_x = between(10, BUFFER_W - 50);

    for (int i = 0; i < ALIENS_N; i++)
    {
        if (!aliens[i].used)
        {
            // if this alien is unused, should it spawn?
            if (new_quota > 0)
            {
                new_x += between(40, 80);
                if (new_x > (BUFFER_W - 60))
                    new_x -= (BUFFER_W - 60);

                aliens[i].x = new_x;

                aliens[i].y = between(-40, -30);
                aliens[i].type = between(0, ALIEN_TYPE_N);
                aliens[i].shot_timer = between(1, 99);
                aliens[i].blink = 0;
                aliens[i].used = true;

                switch (aliens[i].type)
                {
                case ALIEN_TYPE_BUG:
                    aliens[i].life = 4;
                    break;
                case ALIEN_TYPE_ARROW:
                    aliens[i].life = 2;
                    break;
                case ALIEN_TYPE_THICCBOI:
                    aliens[i].life = 12;
                    break;
                }

                new_quota--;
            }
            continue;
        }

        switch (aliens[i].type)
        {
        case ALIEN_TYPE_BUG:
            if (frames % 2)
                aliens[i].y++;
            break;

        case ALIEN_TYPE_ARROW:
            aliens[i].y++;
            break;

        case ALIEN_TYPE_THICCBOI:
            if (!(frames % 4))
                aliens[i].y++;
            break;
        }

        if (aliens[i].y >= BUFFER_H)
        {
            aliens[i].used = false;
            continue;
        }

        if (aliens[i].blink)
            aliens[i].blink--;

        if (shots_collide(false, aliens[i].x, aliens[i].y, ALIEN_W[aliens[i].type], ALIEN_H[aliens[i].type]))
        {
            aliens[i].life--;
            aliens[i].blink = 4;
        }

        int cx = aliens[i].x + (ALIEN_W[aliens[i].type] / 2);
        int cy = aliens[i].y + (ALIEN_H[aliens[i].type] / 2);

        if (aliens[i].life <= 0)
        {
            fx_add(false, cx, cy);

            switch (aliens[i].type)
            {
            case ALIEN_TYPE_BUG:
                score += 200;
                break;

            case ALIEN_TYPE_ARROW:
                score += 150;
                break;

            case ALIEN_TYPE_THICCBOI:
                score += 800;
                fx_add(false, cx - 10, cy - 4);
                fx_add(false, cx + 4, cy + 10);
                fx_add(false, cx + 8, cy + 8);
                break;
            }

            aliens[i].used = false;
            continue;
        }

        aliens[i].shot_timer--;
        if (aliens[i].shot_timer == 0)
        {
            switch (aliens[i].type)
            {
            case ALIEN_TYPE_BUG:
                shots_add(false, false, cx, cy);
                aliens[i].shot_timer = 150;
                break;
            case ALIEN_TYPE_ARROW:
                shots_add(false, true, cx, aliens[i].y);
                aliens[i].shot_timer = 80;
                break;
            case ALIEN_TYPE_THICCBOI:
                shots_add(false, true, cx - 5, cy);
                shots_add(false, true, cx + 5, cy);
                shots_add(false, true, cx - 5, cy + 8);
                shots_add(false, true, cx + 5, cy + 8);
                aliens[i].shot_timer = 200;
                break;
            }
        }
    }
}

void aliens_draw()
{
    for (int i = 0; i < ALIENS_N; i++)
    {
        if (!aliens[i].used)
            continue;
        if (aliens[i].blink > 2)
            continue;

        al_draw_bitmap(sprites.alien[aliens[i].type], aliens[i].x, aliens[i].y, 0);
    }
}