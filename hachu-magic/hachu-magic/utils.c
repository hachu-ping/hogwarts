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
    int x, y;  // 위치
    int w, h;  // 크기
    double last_attack_time;  // 공격 쿨타임 체크용 (초 단위 Allegro 시간)
} CAT;
;

CAT cat;
int current_round = 1;

void magic_attack(int x, int y, int dir)
{
    // 콘솔에 입력 방향 출력 (테스트용)
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

    // TODO: 나중에 마법 발사 로직 추가
}


void cat_init()
{
    cat.x = 700;  // 중앙
    cat.y = 400;
    cat.w = 150;    // 고양이 너비
    cat.h = 150;    // 고양이 높이

    cat.last_attack_time = al_get_time();  // 현재 시간으로 초기화  // 초기화: 공격 가능 상태로 만듦
}

void cat_update()
{
    // TODO 
    // 라운드마다 고양이 위치 고정
    switch (current_round)
    {
    case 1:
        cat.x = 700;  // 중앙
        cat.y = 400;
        break;
    case 2:
        cat.x = 350;  // 왼쪽 중간
        cat.y = 400;
        break;
    case 3:
        cat.x = 1050; // 오른쪽 중간
        cat.y = 400;
        break;
    default:
        cat.x = 700;
        cat.y = 400;
        break;
    }

    double now = al_get_time();

    // 쿨타임 체크 (0.2초 경과 여부)
    if (now - cat.last_attack_time >= 0.2)                                            // 키가 눌린 상태고 이번 프레임에 처음 눌린 것"과 정확히 일치할 때만 true
    {                                                      // (KEY_DOWN | KEY_SEEN)) 
        int left = (key[ALLEGRO_KEY_LEFT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;          // 키가 눌린 상태이고, 이번 프레임에 처음 눌린 상태인가?
        int right = (key[ALLEGRO_KEY_RIGHT] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int up = (key[ALLEGRO_KEY_UP] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;
        int down = (key[ALLEGRO_KEY_DOWN] == (KEY_DOWN | KEY_SEEN)) ? 1 : 0;

        int total_pressed = left + right + up + down;

        // 오직 한 개 방향키만 눌렸을 때만 유효
        if (total_pressed == 1)
        {

            int input_dir = ALLEGRO_KEY_UNKNOWN;

            if (left)  input_dir = ALLEGRO_KEY_LEFT;
            else if (right) input_dir = ALLEGRO_KEY_RIGHT;
            else if (up)    input_dir = ALLEGRO_KEY_UP;
            else if (down)  input_dir = ALLEGRO_KEY_DOWN;

            // 마법 공격 함수 호출
            magic_attack(cat.x, cat.y, input_dir);

            // 마지막 공격 시간 갱신
            cat.last_attack_time = now;
        }
    }
}





void cat_draw()
{
    // 테스트용: 고양이를 사각형으로 표시 (50x50 크기)
    ALLEGRO_COLOR cat_color = al_map_rgb(255, 0, 0);  // 빨간색

    al_draw_filled_rectangle(cat.x, cat.y, cat.x + cat.w, cat.y + cat.h, cat_color);
}















