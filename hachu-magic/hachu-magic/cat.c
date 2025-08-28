
#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>

#include "cat.h"
#include "game_system.h"

cat_t g_cat;

extern unsigned char g_key[ALLEGRO_KEY_MAX];


void DEBUG_init_cat(void)
{
    g_cat.pos_x = 700;
    g_cat.pos_y = 400;
    g_cat.size_w = 150;
    g_cat.size_h = 150;
    g_cat.attack_delay = 0.2;

    // ���� �ð����� �ʱ�ȭ  
    // �ʱ�ȭ: ���� ���� ���·� ����
    g_cat.last_attack_time = al_get_time();
}

//TODO: ������������ ��ȿ�� �־��ֵ��� ����
void init_cat()
{
    g_cat.pos_x = 700;
    g_cat.pos_y = 400;
    g_cat.size_w = 150;
    g_cat.size_h = 150; 
    g_cat.attack_delay = 0.2;

    // ���� �ð����� �ʱ�ȭ  
    // �ʱ�ȭ: ���� ���� ���·� ����
    g_cat.last_attack_time = al_get_time();

}

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



void update_cat()
{
    // TODO 
#if 0
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
#endif
    //printf("cat_update() �Լ� ����\n");
    double now = al_get_time();

    // ��Ÿ�� üũ (0.2�� ��� ����)
    if (now - g_cat.last_attack_time >= 03)
        // Ű�� ���� ���°� �̹� �����ӿ� ó�� ���� ��"�� ��Ȯ�� ��ġ�� ���� true
    {
        // printf("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, cat.last_attack_time, now - cat.last_attack_time);                                                   // (KEY_DOWN | KEY_SEEN)) 
        int left = (g_key[ALLEGRO_KEY_LEFT] == KEY_DOWN) ? 1 : 0;          // Ű�� ���� �����̰�, �̹� �����ӿ� ó�� ���� �����ΰ�?
        int right = (g_key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        int up = (g_key[ALLEGRO_KEY_UP] == KEY_DOWN) ? 1 : 0;
        int down = (g_key[ALLEGRO_KEY_DOWN] == KEY_DOWN) ? 1 : 0;

        /*/
        int left = (g_key[ALLEGRO_KEY_LEFT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;          // Ű�� ���� �����̰�, �̹� �����ӿ� ó�� ���� �����ΰ�?
        int right = (g_key[ALLEGRO_KEY_RIGHT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int up = (g_key[ALLEGRO_KEY_UP] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int down = (g_key[ALLEGRO_KEY_DOWN] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        */
        // �ڵ� ���� ����
        // printf("LEFT key raw state: %d, %d\n\n", g_key[ALLEGRO_KEY_LEFT], left);
        // printf("RIGHT key raw state: %d, %d\n\n", g_key[ALLEGRO_KEY_RIGHT], right);
        // printf("UP key raw state: %d, %d\n\n", g_key[ALLEGRO_KEY_UP], up);
        // printf("DOWN key raw state: %d, %d\n\n", g_key[ALLEGRO_KEY_DOWN], down);
        int total_pressed = left + right + up + down;

        // ���� �� �� ����Ű�� ������ ���� ��ȿ
        if (total_pressed == 1)
        {

            int input_dir = 0;
            // printf("input_dir %d\n\n\n\n\n", input_dir);

            if (left)  input_dir = ALLEGRO_KEY_LEFT;
            else if (right) input_dir = ALLEGRO_KEY_RIGHT;
            else if (up)    input_dir = ALLEGRO_KEY_UP;
            else if (down)  input_dir = ALLEGRO_KEY_DOWN;
            printf("input_dir %d\n\n\n\n\n", input_dir);
            printf("left %d, right: %d, up : %d, down : %d", left, right, up, down);
            // ���� ���� �Լ� ȣ��
            magic_attack(g_cat.pos_x, g_cat.pos_y, input_dir);

            // ������ ���� �ð� ����
            g_cat.last_attack_time = now;
        }
    }
}
