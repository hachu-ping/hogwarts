#include <stdio.h>

#include "utils.h"
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>


void must_init(bool test, const char* description) {
    if (test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}
// --- keyboard ---

#define KEY_SEEN     1
#define KEY_DOWN     2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init()
{
    memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
    switch (event->type)
    {
    case ALLEGRO_EVENT_TIMER:
        for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
            key[i] &= ~KEY_SEEN;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        key[event->keyboard.keycode] = KEY_SEEN | KEY_DOWN;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        key[event->keyboard.keycode] &= ~KEY_DOWN;
        break;
    }
}

typedef struct {
    int x, y;  // ��ġ
    int w, h;  // ũ��
    double last_attack_time;  // ���� ��Ÿ�� üũ�� (�� ���� Allegro �ð�)
} CAT;
;

CAT cat;
int current_round = 1;

void magic_attack(int x, int y, int dir)
{
    // �ֿܼ� �Է� ���� ��� (�׽�Ʈ��)
    switch (dir)
    {
    case ALLEGRO_KEY_LEFT:
        printf("Magic attack: LEFT\n");
        break;
    case ALLEGRO_KEY_RIGHT:
        printf("Magic attack: RIGHT\n");
        break;
    case ALLEGRO_KEY_UP:
        printf("Magic attack: UP\n");
        break;
    case ALLEGRO_KEY_DOWN:
        printf("Magic attack: DOWN\n");
        break;
    default:
        printf("Magic attack: NONE\n");
        break;
    }

    // TODO: ���߿� ���� �߻� ���� �߰�
}


void cat_init()
{
    cat.x = 700;  // �߾�
    cat.y = 400;
    cat.w = 150;    // ����� �ʺ�
    cat.h = 150;    // ����� ����

    cat.last_attack_time = al_get_time();  // ���� �ð����� �ʱ�ȭ  // �ʱ�ȭ: ���� ���� ���·� ����
}

void cat_update()
{
    // TODO 
    // ���帶�� ����� ��ġ ����
    switch (current_round)
    {
    case 1:
        cat.x = 700;  // �߾�
        cat.y = 400;
        break;
    case 2:
        cat.x = 350;  // ���� �߰�
        cat.y = 400;
        break;
    case 3:
        cat.x = 1050; // ������ �߰�
        cat.y = 400;
        break;
    default:
        cat.x = 700;
        cat.y = 400;
        break;
    }

    double now = al_get_time();

    // ��Ÿ�� üũ (0.2�� ��� ����)
    if (now - cat.last_attack_time >= 0.2)                                            // Ű�� ���� ���°� �̹� �����ӿ� ó�� ���� ��"�� ��Ȯ�� ��ġ�� ���� true
    {                                                      // (KEY_DOWN | KEY_SEEN)) 
        int left = (key[ALLEGRO_KEY_LEFT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;          // Ű�� ���� �����̰�, �̹� �����ӿ� ó�� ���� �����ΰ�?
        int right = (key[ALLEGRO_KEY_RIGHT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int up = (key[ALLEGRO_KEY_UP] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int down = (key[ALLEGRO_KEY_DOWN] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;

        int total_pressed = left + right + up + down;

        // ���� �� �� ����Ű�� ������ ���� ��ȿ
        if (total_pressed == 1)
        {

            int input_dir = ALLEGRO_KEY_UNKNOWN;

            if (left)  input_dir = ALLEGRO_KEY_LEFT;
            else if (right) input_dir = ALLEGRO_KEY_RIGHT;
            else if (up)    input_dir = ALLEGRO_KEY_UP;
            else if (down)  input_dir = ALLEGRO_KEY_DOWN;

            // ���� ���� �Լ� ȣ��
            magic_attack(cat.x, cat.y, input_dir);

            // ������ ���� �ð� ����
            cat.last_attack_time = now;
        }
    }
}





void cat_draw()
{
    // �׽�Ʈ��: ����̸� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // ������

    al_draw_filled_rectangle(cat.x, cat.y, cat.x + cat.w, cat.y + cat.h, cat_color);
}















