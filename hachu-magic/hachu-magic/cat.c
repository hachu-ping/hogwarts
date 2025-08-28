
#include "cat.h"
#include "enemy.h"
#include "utils.h"
#include "magic.h"
#include <allegro5/keycodes.h>

#include <stdio.h>

cat_t g_cat;

#define KEY_SEEN     1
#define KEY_DOWN     2

extern unsigned char key[ALLEGRO_KEY_MAX];

#define MAX_ENEMY 15
extern enemy_t g_enemy_list[MAX_ENEMY];

#define MAX_MAGIC 20
extern magic_t g_magic_list[MAX_MAGIC];

void init_cat()
{
    g_cat.pos_x = 700;  // �߾�
    g_cat.pos_y = 400;
    g_cat.size_w = 150;    // ����� �ʺ�
    g_cat.size_h = 150;    // ����� ����

    g_cat.last_attack_time = al_get_time();  // ���� �ð����� �ʱ�ȭ 
}


void update_cat()
{
    // TODO 
    /*
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
    */
    
    double now = al_get_time();

    // ��Ÿ�� üũ (0.2�� ��� ����)
    if (now - g_cat.last_attack_time >= 0.2)
        
    {
        // printf("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, cat.last_attack_time, now - cat.last_attack_time);                                                   // (KEY_DOWN | KEY_SEEN)) 
        int left = (key[ALLEGRO_KEY_LEFT] == KEY_DOWN) ? 1 : 0;          
        int right = (key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        int up = (key[ALLEGRO_KEY_UP] == KEY_DOWN ) ? 1 : 0;
        int down = (key[ALLEGRO_KEY_DOWN] == KEY_DOWN) ? 1 : 0;

        
        
        int total_pressed = left + right + up + down;
        
        // ���� �� �� ����Ű�� ������ ���� ��ȿ
        if (total_pressed == 1)
        {
            int keycode = 0;  //  ���⼭ Allegro Ű�ڵ� ��������� ����
           

            if (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else if (down)  keycode = ALLEGRO_KEY_DOWN;
           
            printf("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);

            // ���� ���� �Լ� ȣ��
            Direction input_dir = keycode_to_direction(keycode);
            printf("input_dir(enum) = %d\n", input_dir);  // 1~4 ��� Ȯ��

            handle_input_and_create_magic(input_dir);

            // ������ ���� �ð� ����
            g_cat.last_attack_time = now;
        }
    }
}
void create_magic(int, int, int, int, float, char, enemy_t*);
void handle_input_and_create_magic(int input_dir)

{
    
    for (int i = 0; i < MAX_ENEMY; i++) {
        enemy_t* e = &g_enemy_list[i];

        
        // 1. ���� ��� ���̰�
        // 2. ������ �ƴϸ�
        // 3. ���� ���� ������ �ְ�
        printf("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            i, e->used, e->is_invincible, e->received_attack_count, e->life);

        if (e->used && !e->is_invincible && e->received_attack_count < e->life)
        {


            char expected_dir = e->pattern[e->received_attack_count];
            
            // 4. �Է� ������ ���ϰ� ��ġ�ϸ�
            if (expected_dir == input_dir)
            {
                printf("[MAGIC-LOGIC] �� #%d: ���� ��ġ (%d)\n", i, input_dir);

                // 5. ���� ���� (��ȯ�� ���� ȣ�⸸)
                create_magic(g_cat.pos_x, g_cat.pos_y, 20, 20, 10.0f, input_dir, e);

                // 6. ���� �� �ܰ� ���� ����
                e->received_attack_count++;


            }
            else {
                printf("[MAGIC-LOGIC] �� #%d: ���� ����ġ (�Է�: %d, ��밪: %d)\n", i, input_dir, e->pattern[e->received_attack_count]);
            }
        }
    }
}

void create_magic(int x, int y, int size_w, int size_h, float velocity, char type, enemy_t* target)
{
    for (int i = 0; i < MAX_MAGIC; i++) {
        if (g_magic_list[i].velocity == 0) {  // ��� �ִ� ���� �߰�
            g_magic_list[i].pos_x = x;
            g_magic_list[i].pos_y = y;
            g_magic_list[i].size_w = size_w;
            g_magic_list[i].size_h = size_h;
            g_magic_list[i].velocity = velocity;
            g_magic_list[i].type = type;
            g_magic_list[i].target_ptr = (void*)target;

            //  ���� ��Ȳ �α� ���
            printf("[MAGIC] ���� #%d�� ���� ������ (����: %d, �ӵ�: %.1f)\n", i, type, velocity);
            return;
        }
    }

    //  ��� ������ �� á�� ���
    printf("[MAGIC] ���� ����! ��� ������ ���� ������ �����ϴ�.\n");
}

void draw_cat()
{
    // �׽�Ʈ��: ����̸� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // ������

    al_draw_filled_rectangle(g_cat.pos_x, g_cat.pos_y, g_cat.pos_x + g_cat.size_w, g_cat.pos_y + g_cat.size_h, cat_color);
}



/*
void DEBUG_init_cat(void) 
{
	// TODO: Modify to valid values
	g_cat.size_w = 200;
	g_cat.size_h = 200;
	g_cat.pos_x = 500;
	g_cat.pos_y = 500;
	g_cat.last_attack_time = 0.2;
}
*/

