#include "enemy.h"
#include "magic.h"

// TODO: define max magic number
magic_t magics[15];

void DEBUG_init_magic(void) {
	// for debugging
	extern enemy_t enemies[15];

	for (int i = 0; i < 5; i++) {
		magics[i].type = 0;
		magics[i].pos_x = 0;
		magics[i].pos_y = 0;
		magics[i].size_w = 0;
		magics[i].size_h = 0;
		magics[i].velocity = 1.0;
		magics[i].target_ptr = &enemies[i];
	}
}
//캐릭터 생성은 되는데 이동이 안 됩니다
/*
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

//임시 전역 변수 설정
long frames; //초당 프레임 정의
int heartsp_x = 700; //하츄핑 중심좌표 선언
int heartsp_y = 400;

void must_init(bool test, const char* description) {
    if (test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

int between(int lo, int hi)
{
    return lo + (rand() % (hi - lo));
}

//임시 적 비트맵 로드용 스프라이트
typedef struct SPRITES {
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* enemy[3];
}SPRITES;
SPRITES sprites;

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

void sprites_init() {
    sprites._sheet = al_load_bitmap("enemy.png");
    must_init(sprites._sheet, "spritesheet");

    sprites.enemy[0] = sprite_grab(86, 90, 240, 300);
    sprites.enemy[1] = sprite_grab(424, 93, 240, 300);
    sprites.enemy[2] = sprite_grab(751, 93, 240, 300);
}

//적 관련 변수 정의
typedef enum ENEMY_TYPE {
    ENEMY_TYPE_STAGE1 = 1,
    ENEMY_TYPE_STAGE2,
    ENEMY_TYPE_STAGE3
}ENEMY_TYPE;

typedef enum ENEMY_SPAWN {
    ENEMY_UP = 0,
    ENEMY_DOWN,
    ENEMY_LEFT,
    ENEMY_RIGHT
}ENEMY_TYPE;

typedef struct ENEMY {
    ENEMY_TYPE type;
    int x, y;
    int life;
    int pattern;
    int velocity;
    bool used; //적이 생성 되었는지 여부를 판별하기 위해 사용 1 : 사용됨, 0 : 사용되지 않음
    bool invinc; //스폰시 무적 설정 후 해제 용도. 1 : 무적, 0 : 공격 가능
}ENEMY;

#define ENEMY_N_1 10 //적 생성 마릿수를 임시로 설정
ENEMY enemy[ENEMY_N_1];

void enemies_init() {
    for (int i = 0; i < ENEMY_N_1; i++)
        enemy[i].used = false;
}

void enemies_update() { //나중에 enemy[i]에 대한 typedef도 다시 진행할 것!
    int spawn = (frames % 120) ? 0 : 1; //1마리 생성

    if (spawn) {
        for (int i = 0; i < ENEMY_N_1; ++i) {
            if (!enemy[i].used) {
                int where = between(0, 3);
                switch (where) {
                case ENEMY_UP:
                    enemy[i].x = rand() % 1400;
                    enemy[i].y = -50;
                    break;

                case ENEMY_DOWN:
                    enemy[i].x = rand() % 1400;
                    enemy[i].y = 800 + 50;
                    break;
                case ENEMY_LEFT:
                    enemy[i].x = -50;
                    enemy[i].y = rand() % 800;
                    break;
                case ENEMY_RIGHT:
                    enemy[i].x = 1400 + 50;
                    enemy[i].y = rand() % 800;
                    break;
                }
            }
            enemy[i].type = ENEMY_TYPE_STAGE1;
            enemy[i].life = 50;
            enemy[i].pattern = 3412;
            enemy[i].velocity = 2;
            enemy[i].used = 1;
            enemy[i].invinc = 1;
        }
    }
}

void moveAlien(ENEMY* a) {
    int i;

    int dx = heartsp_x - a->x;
    int dy = heartsp_y - a->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist == 0) { return; }


    switch (a->pattern) {
    case 0:
        a->x += (int)(dx / dist * a->velocity);
        a->y += (int)(dy / dist * a->velocity);
        printf("(%d, %d)", a->x, a->y);
        break;
    case 1:
        a->x += (int)(dx / dist * a->velocity) + (rand() % 3 - 1);
        a->y += (int)(dy / dist * a->velocity) + (rand() % 3 - 1);
        printf("(%d, %d)", a->x, a->y);
        break;
    case 2:
        a->x += (int)(dx / dist * a->velocity) + sin(a->y * 0.05) * 2;
        a->y += (int)(dy / dist * a->velocity);
        printf("(%d, %d)", a->x, a->y);
        break;
    }
}

void enemies_move() {
    for (int i = 0; i < ENEMY_N_1; i++) {
        if (!enemy[i].used) {
            //printf("moved ");
            continue;
        }

        // 1. 방향 벡터 구하기
        float dx = heartsp_x - enemy[i].x;
        float dy = heartsp_y - enemy[i].y;

        // 2. 벡터 길이(거리) 구해서 정규화
        float len = sqrt(dx * dx + dy * dy);
        if (len == 0) continue; // 이미 겹침

        dx /= len; // 단위 벡터
        dy /= len;

        // 3. 속도만큼 이동
        enemy[i].x += (int)(dx * enemy[i].velocity);
        enemy[i].y += (int)(dy * enemy[i].velocity);
    }
}

void enemies_draw() {
    for (int i = 0; i < ENEMY_N_1; i++) {
        if (!enemy[i].used)
            continue;
        al_draw_bitmap(sprites.enemy[enemy[i].type], enemy[i].x, enemy[i].y, 0);
    }
}


int main() {
    must_init(al_init(), "allegro");
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");
    al_start_timer(timer);

    // initialize addon for load png image
    al_init_image_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(1400, 800);
    must_init(disp, "display");

    // load placeholder image
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background-image");
    sprites_init();
    al_draw_bitmap(background, 0, 0, 0);
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(background, 0, 0, 640, 430, 0, 0, 1400, 800, 0);

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    must_init(queue, "queue");



    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_display_event_source(timer));


    bool done = false;

    while (!done) {
        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        int i = 0;

        switch (event.type) {
            /*
        case ALLEGRO_EVENT_TIMER:
            frames++;
            //enemies_draw();
            enemies_update();

            //for (int i = 0; i < ENEMY_N_1; i++) {
                if (enemy[i].used) {
                    moveAlien(&enemy[i]);
                }
            //
            moveAlien(&enemy[i]);
            enemies_draw();
            //enemies_move();
            //printf("DEBUG");
            i++;
            break;
            

        case ALLEGRO_EVENT_TIMER:
            frames++;
            enemies_update();
            //enemies_move();
            moveAlien(&enemy[1]);


            //al_clear_to_color(al_map_rgb(0, 0, 0)); // 화면 클리어
            //al_draw_bitmap(background, 0, 0, 0);
            enemies_draw();

            al_flip_display();
            break;



        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }


    }

    al_destroy_display(disp);

    return 0;
}

*/