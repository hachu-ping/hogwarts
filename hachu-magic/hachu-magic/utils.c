

#include <stdio.h>


#include <allegro5/allegro5.h>
#include <allegro5/keycodes.h>
#include <allegro5/allegro_primitives.h>

#include "utils.h"
#include "enemy.h"
#include "magic.h"




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

Direction keycode_to_direction(int keycode)
{
    switch (keycode) {
    case ALLEGRO_KEY_LEFT: return DIR_LEFT;
    case ALLEGRO_KEY_RIGHT: return DIR_RIGHT;
    case ALLEGRO_KEY_UP: return DIR_UP;
    case ALLEGRO_KEY_DOWN: return DIR_DOWN;
    default: return DIR_NONE;
    }
}
/*


typedef struct {
    int pos_x, pos_y;  // ��ġ
    int size_w, size_h;  // ũ��
    double last_attack_time;  // ���� ��Ÿ�� üũ�� (�� ���� Allegro �ð�)
} CAT;


CAT cat;


// ��ġ �Űܾ� ��
typedef enum {
    DIR_NONE = 0,
    DIR_LEFT = 1,
    DIR_RIGHT = 2,
    DIR_UP = 3,
    DIR_DOWN = 4
} Direction;

Direction keycode_to_direction(int keycode)
{
    switch (keycode) {
    case ALLEGRO_KEY_LEFT: return DIR_LEFT;
    case ALLEGRO_KEY_RIGHT: return DIR_RIGHT;
    case ALLEGRO_KEY_UP: return DIR_UP;
    case ALLEGRO_KEY_DOWN: return DIR_DOWN;
    default: return DIR_NONE;
    }
}





#define MAX_MAGIC 20
extern magic_t g_magic_list[MAX_MAGIC];
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



#define MAX_ENEMY 15
extern enemy_t g_enemy_list[MAX_ENEMY];

#include <stdio.h>
#include "enemy.h"
#include "magic.h"

// �ܺ� ���� ������
extern CAT cat;
extern enemy_t g_enemy_list[MAX_ENEMY];

void handle_input_and_create_magic(int input_dir)

{
    // printf("\nhandle �Լ� ����-1\n");
    for (int i = 0; i < MAX_ENEMY; i++) {
        enemy_t* e = &g_enemy_list[i];
        
        // 
        // 1. ���� ��� ���̰�
        // 2. ������ �ƴϸ�
        // 3. ���� ���� ������ �ְ�
         printf("[DEBUG] enemy[%d] used: %d, invincible: %d, received_attack_count: %d, life: %d\n",
            i, e->used, e->is_invincible, e->received_attack_count, e->life);

        if (e->used && !e->is_invincible && e->received_attack_count < e->life)
        {
           

            char expected_dir = e->pattern[e->received_attack_count];
            //printf("%d, %d\n", input_dir,  e->pattern[e->received_attack_count]);
            // 4. �Է� ������ ���ϰ� ��ġ�ϸ�
            if (expected_dir == input_dir)
            {
                printf("[MAGIC-LOGIC] �� #%d: ���� ��ġ (%d)\n", i, input_dir);

                // 5. ���� ���� (��ȯ�� ���� ȣ�⸸)
                create_magic(cat.pos_x, cat.pos_y, 20, 20, 10.0f, input_dir, e);

                // 6. ���� �� �ܰ� ���� ����
                e->received_attack_count++;

                
            }
            else {
                printf("[MAGIC-LOGIC] �� #%d: ���� ����ġ (�Է�: %d, ��밪: %d)\n", i, input_dir, e->pattern[e->received_attack_count]);
            }
        }
    }
}



void cat_init()
{
    cat.pos_x = 700;  // �߾�
    cat.pos_y = 400;
    cat.size_w = 150;    // ����� �ʺ�
    cat.size_h = 150;    // ����� ����

    cat.last_attack_time = al_get_time();  // ���� �ð����� �ʱ�ȭ  // �ʱ�ȭ: ���� ���� ���·� ����
    //printf("cat_init() �Լ� ����\n");
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
    
    //printf("cat_update() �Լ� ����\n");
    double now = al_get_time();

    // ��Ÿ�� üũ (0.2�� ��� ����)
    if (now - cat.last_attack_time >= 1)     
        
    {
        // printf("now: %.2f, last_attack_time: %.2f, diff: %.2f\n", now, cat.last_attack_time, now - cat.last_attack_time);                                                   // (KEY_DOWN | KEY_SEEN)) 
        int left = (key[ALLEGRO_KEY_LEFT] == KEY_DOWN) ? 1 : 0;          
        int right = (key[ALLEGRO_KEY_RIGHT] == KEY_DOWN) ? 1 : 0;
        int up = (key[ALLEGRO_KEY_UP] == KEY_DOWN ) ? 1 : 0;
        int down = (key[ALLEGRO_KEY_DOWN] == KEY_DOWN) ? 1 : 0;

        
        // printf("LEFT key raw state: %d, %d\n\n", key[ALLEGRO_KEY_LEFT], left);
        // printf("RIGHT key raw state: %d, %d\n\n", key[ALLEGRO_KEY_RIGHT], right);
        // printf("UP key raw state: %d, %d\n\n", key[ALLEGRO_KEY_UP], up);
        // printf("DOWN key raw state: %d, %d\n\n", key[ALLEGRO_KEY_DOWN], down);
        int total_pressed = left + right + up + down;
        
        // ���� �� �� ����Ű�� ������ ���� ��ȿ
        if (total_pressed == 1)
        {
            int keycode = 0;  //  ���⼭ Allegro Ű�ڵ� ��������� ����
            // int input_dir = 0;
            // printf("input_dir %d\n\n\n\n\n", input_dir);

            if (left)  keycode = ALLEGRO_KEY_LEFT;
            else if (right) keycode = ALLEGRO_KEY_RIGHT;
            else if (up)    keycode = ALLEGRO_KEY_UP;
            else if (down)  keycode = ALLEGRO_KEY_DOWN;
            // printf("input_dir %d\n\n\n\n\n", input_dir);
            printf("left %d, right: %d, up : %d, down : %d\n", left, right, up, down);
            // ���� ���� �Լ� ȣ��
            //magic_attack(cat.x, cat.y, input_dir);

            Direction input_dir = keycode_to_direction(keycode);
            printf("input_dir(enum) = %d\n", input_dir);  // 1~4 ��� Ȯ��

            handle_input_and_create_magic(input_dir);

            // ������ ���� �ð� ����
            cat.last_attack_time = now;
        }
    }
}





void cat_draw()
{
    // �׽�Ʈ��: ����̸� �簢������ ǥ�� (50x50 ũ��)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // ������

    al_draw_filled_rectangle(cat.pos_x, cat.pos_y, cat.pos_x + cat.size_w, cat.pos_y + cat.size_h, cat_color);
}

*/














