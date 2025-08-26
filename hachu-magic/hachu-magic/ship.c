#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "example.h"

extern SPRITES sprites;
extern unsigned char key[ALLEGRO_KEY_MAX];

#define SHIP_SPEED 3
#define SHIP_MAX_X (BUFFER_W - SHIP_W)
#define SHIP_MAX_Y (BUFFER_H - SHIP_H)


SHIP ship;

void ship_init()
{
    ship.x = (BUFFER_W / 2) - (SHIP_W / 2);
    ship.y = (BUFFER_H / 2) - (SHIP_H / 2);
    ship.shot_timer = 0;
    ship.lives = 3;
    ship.respawn_timer = 0;
    ship.invincible_timer = 120;
}

void ship_update()
{
    if (ship.lives < 0)
        return;

    if (ship.respawn_timer)
    {
        ship.respawn_timer--;
        return;
    }

    if (key[ALLEGRO_KEY_LEFT])
        ship.x -= SHIP_SPEED;
    if (key[ALLEGRO_KEY_RIGHT])
        ship.x += SHIP_SPEED;
    if (key[ALLEGRO_KEY_UP])
        ship.y -= SHIP_SPEED;
    if (key[ALLEGRO_KEY_DOWN])
        ship.y += SHIP_SPEED;

    if (ship.x < 0)
        ship.x = 0;
    if (ship.y < 0)
        ship.y = 0;

    if (ship.x > SHIP_MAX_X)
        ship.x = SHIP_MAX_X;
    if (ship.y > SHIP_MAX_Y)
        ship.y = SHIP_MAX_Y;

    if (ship.invincible_timer)
        ship.invincible_timer--;
    else
    {
        if (shots_collide(true, ship.x, ship.y, SHIP_W, SHIP_H))
        {
            int x = ship.x + (SHIP_W / 2);
            int y = ship.y + (SHIP_H / 2);
            fx_add(false, x, y);
            fx_add(false, x + 4, y + 2);
            fx_add(false, x - 2, y - 4);
            fx_add(false, x + 1, y - 5);

            ship.lives--;
            ship.respawn_timer = 90;
            ship.invincible_timer = 180;
        }
    }

    if (ship.shot_timer)
        ship.shot_timer--;
    else if (key[ALLEGRO_KEY_X])
    {
        int x = ship.x + (SHIP_W / 2);
        if (shots_add(true, false, x, ship.y))
            ship.shot_timer = 5;
    }
}

void ship_draw()
{
    if (ship.lives < 0)
        return;
    if (ship.respawn_timer)
        return;
    if (((ship.invincible_timer / 2) % 3) == 1)
        return;

    al_draw_bitmap(sprites.ship, ship.x, ship.y, 0);
}