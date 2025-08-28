
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "game_system.h"

// --- keyboard ---


unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_update(ALLEGRO_EVENT* event)
{

    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:

        //printf("DEBUG -- Key ����: %d\n", event->keyboard.keycode);  // �� � Ű���� ���
        key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        printf("DEBUG -- Key ����: %d\n", event->keyboard.keycode);  // �� � Ű���� ���
        break;
    case ALLEGRO_EVENT_KEY_UP:
        // printf("DEBUG -- Key ����: %d\n", event->keyboard.keycode);  // �� � Ű���� ���
        key[event->keyboard.keycode] &= ~KEY_DOWN;
        printf("DEBUG -- Key ����: %d\n", event->keyboard.keycode);  // �� � Ű���� ���
        break;
    }
}