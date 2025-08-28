//제각각의 속도를 한번 처리해봄
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_ALIENS 20

typedef struct {
    float x, y;    // 속도를 정밀하게 하기 위해 float사용
    float speed;         //다양한 속도 표현이 가능하여 int 아닌 float를 사용
    bool alive;
    int targetX, targetY;  // 목표 지점은 int로 해도 괜찮ㅎㅎ
} Alien;

typedef struct {
    int x, y;
} Player;

Player player;
Alien aliens[MAX_ALIENS];

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* player_img;
ALLEGRO_BITMAP* alien_img;

// Alien 생성 (사방에서 등장, 겹치지 않게 생성)
Alien createAlien(int alienIndex, int totalAliens) {
    Alien a;

    // 속도를 1.0f ~ 2.99f 사이 랜덤값으로 지정
    a.speed = 1.0f + (rand() % 200) / 100.0f;

    a.alive = true;

    int maxAttempts = 100;
    bool validPosition = false;

    while (!validPosition && maxAttempts-- > 0) {
        int side = rand() % 4;
        switch (side) {
        case 0: a.x = -50.0f;      //화면 왼쪽 바깥쪽 (x = -50)에서 y 위치는 0 ~ SCREEN_H 범위 내에서 랜덤       
            a.y = (float)(rand() % SCREEN_H); 
            break;
        case 1: a.x = (float)(SCREEN_W + 50);    //화면 오른쪽 바깥 (x = SCREEN_W + 50)에서, Y의 위치는 y 위치는 0 ~ SCREEN_H
            a.y = (float)(rand() % SCREEN_H); 
            break;
        case 2: a.x = (float)(rand() % SCREEN_W);   //화면 위쪽 바깥 (y = -50) 에서 ,X 의 위치는 0 ~ SCREEN_W
            a.y = -50.0f;              
            break;
        case 3: a.x = (float)(rand() % SCREEN_W);   //화면 오른쪽 바깥 (x = SCREEN_W + 50) 에서 y 의 위치는 0 ~ SCREEN_H
            a.y = (float)(SCREEN_H + 50);    
            break;
        }

        // 목표 위치: 플레이어 위치 + 랜덤 ±10px 편차
        a.targetX = player.x + (rand() % 21 - 10);
        a.targetY = player.y + (rand() % 21 - 10);

        validPosition = true;
        for (int i = 0; i < alienIndex; i++) {
            if (!aliens[i].alive) continue;
            float dx = aliens[i].x - a.x;          //기존 외계인과 새 외계인 위치 차이 계산 (거리 계산)
            float dy = aliens[i].y - a.y;
            float dist = sqrtf(dx * dx + dy * dy);      //두 위치 사이릐 거리를 정확하게 비교하기 위해, sqrtf 제곱근 구하는 함수
            if (dist < 40.0f) {                        //겹침 방지
                validPosition = false;                  //vaildPosition 위치가 유요한지
                break;
            }
        }
    }

    return a;
}

// Alien 이동 (각자 목표 지점으로 이동, 도달 시 죽음)
void moveAlien(Alien* a) {
    if (!a->alive) return;

    float dx = a->targetX - a->x;
    float dy = a->targetY - a->y;
    float dist = sqrtf(dx * dx + dy * dy);    

    if (dist < 2.0f) {
        a->alive = false;
        return;
    }

    a->x += (dx / dist) * a->speed;
    a->y += (dy / dist) * a->speed;
}

// 스테이지 실행
void runStage(int stageNo, int alienCount, ALLEGRO_EVENT_QUEUE* queue) {
    printf("=== Stage %d start (%d aliens , 3 waves) ===\n", stageNo, alienCount);

    for (int wave = 1; wave <= 3; wave++) {
        // Alien 생성
        for (int i = 0; i < alienCount; i++) {
            aliens[i] = createAlien(i, alienCount);
        }

        bool wave_done = false;
        while (!wave_done) {
            // 이벤트 처리 (창 닫기)
            ALLEGRO_EVENT event;
            while (al_get_next_event(queue, &event)) {
                if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return;
            }

            // 이동
            for (int i = 0; i < alienCount; i++) {
                moveAlien(&aliens[i]);
            }

            // 그리기
            al_draw_scaled_bitmap(background, 0, 0,
                al_get_bitmap_width(background), al_get_bitmap_height(background),
                0, 0, SCREEN_W, SCREEN_H, 0);

            al_draw_scaled_bitmap(player_img, 0, 0,
                al_get_bitmap_width(player_img), al_get_bitmap_height(player_img),
                player.x - 25, player.y - 25, 50, 50, 0);

            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    al_draw_scaled_bitmap(alien_img, 0, 0,
                        al_get_bitmap_width(alien_img), al_get_bitmap_height(alien_img),
                        (int)(aliens[i].x) - 20, (int)(aliens[i].y) - 20, 40, 40, 0);
                }
            }

            al_flip_display();
            al_rest(0.02);

            // 모든 Alien 사망 확인
            bool allDead = true;
            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    allDead = false;
                    break;
                }
            }

            if (allDead) {
                printf("Stage %d - Wave %d: All aliens clear\n", stageNo, wave);
                al_rest(0.5);
                wave_done = true;
            }
        }
    }

    printf("=== Stage %d clear! ===\n", stageNo);
}

int main() {
    srand((unsigned)time(NULL));

    al_init();
    al_init_image_addon();

    disp = al_create_display(SCREEN_W, SCREEN_H);

    
    background = al_load_bitmap("placeholder.jpeg");
    player_img = al_load_bitmap("blue.jpeg");
    alien_img = al_load_bitmap("green.jpeg");

    if (!disp || !background || !player_img || !alien_img) {
        printf("fail\n");
        return 1;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(disp));

    player.x = SCREEN_W / 2;
    player.y = SCREEN_H / 2;

    al_draw_scaled_bitmap(background, 0, 0,
        al_get_bitmap_width(background), al_get_bitmap_height(background),
        0, 0, SCREEN_W, SCREEN_H, 0);
    al_draw_scaled_bitmap(player_img, 0, 0,
        al_get_bitmap_width(player_img), al_get_bitmap_height(player_img),
        player.x - 25, player.y - 25, 50, 50, 0);
    al_flip_display();

    runStage(1, 5, queue);
    runStage(2, 7, queue);
    runStage(3, 9, queue);

    al_rest(2.0);

    al_destroy_bitmap(player_img);
    al_destroy_bitmap(alien_img);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}



