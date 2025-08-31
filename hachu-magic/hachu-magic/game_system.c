#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "game_system.h"

unsigned char g_key[ALLEGRO_KEY_MAX];

void keyboard_update(ALLEGRO_EVENT* event)
{

    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            g_key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:

        //printf("DEBUG -- Key 누름: %d\n", event->keyboard.keycode);  // 어떤 키 누르는지 확인
        g_key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        //printf("DEBUG -- Key 누름: %d\n", event->keyboard.keycode);  // 어떤 키 누르는지 확인
        break;
    case ALLEGRO_EVENT_KEY_UP:
        // printf("DEBUG -- Key 뗌: %d\n", event->keyboard.keycode);  // 어떤 키 뗐는지 확인
        g_key[event->keyboard.keycode] &= ~KEY_DOWN;
        //printf("DEBUG -- Key 뗌: %d\n", event->keyboard.keycode);  // 어떤 키 뗐는지 확인
        break;
    }
}