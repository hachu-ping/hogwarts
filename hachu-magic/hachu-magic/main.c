//main일단 기본
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>



int main() {
    must_init(al_init(), "allegro");

    // initialize addon for load png image
    al_init_image_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
    must_init(disp, "display");

    // load placeholder image
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background-image");

    al_rest(0.5);
   
    //al_draw_bitmap(background, 0, 0, 0);
    al_draw_scaled_bitmap(background, 0, 0, 640, 437, 0, 0, 800, 600, 0);
 
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    must_init(queue, "queue");



    al_register_event_source(queue, al_get_display_event_source(disp));
    //al_register_event_source(queue, al_get_timer_event_source(timer));
    //al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;

    while (!done) {
        al_flip_display();

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        switch (event.type) {

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        // use if you need conditional redraw
        // if (redraw && al_is_event_queue_empty(queue)) {
        //    al_flip_display();
        //    redraw = false;
        // }
    }

    al_destroy_display(disp);
    //al_destroy_event_queue(queue);
    //al_destroy_timer(timer);

    return 0;
}


#endif




/*일단 이거 동작 돌아감*/
#if 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_ALIENS 10

typedef struct { int x, y; } Player;
typedef struct { int x, y; float speed; int pattern; } Alien;

Player player;
Alien aliens[MAX_ALIENS];

// Alien 생성 (사방에서 랜덤 등장)
Alien createAlien() {
    Alien a;
    a.speed = 2 + (rand() % 100) / 50.0;
    a.pattern = rand() % 3;
    int side = rand() % 4;

    switch (side) {
    case 0: a.x = -50; a.y = rand() % SCREEN_H; break;
    case 1: a.x = SCREEN_W + 50; a.y = rand() % SCREEN_H; break;
    case 2: a.x = rand() % SCREEN_W; a.y = -50; break;
    case 3: a.x = rand() % SCREEN_W; a.y = SCREEN_H + 50; break;
    }
    return a;
}

// Alien 이동 (player 향해)
void moveAlien(Alien* a) {
    int dx = player.x - a->x;
    int dy = player.y - a->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist == 0) { return; }

    printf("%d %f %f %f\n", dx, dist, a->speed, dx / dist * a->speed);
    switch (a->pattern) {
    case 0:
        a->x += (int)(dx / dist * a->speed);
        a->y += (int)(dy / dist * a->speed);
        break;
    case 1:
        a->x += (int)(dx / dist * a->speed) + (rand() % 3 - 1);
        a->y += (int)(dy / dist * a->speed) + (rand() % 3 - 1);
        break;
    case 2:
        a->x += (int)(dx / dist * a->speed) + sin(a->y * 0.05) * 2;
        a->y += (int)(dy / dist * a->speed);
        break;
    }
}

int main() {
    srand(time(NULL));

    must_init(al_init(), "allegro");
    al_init_image_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    // 절대 경로로 이미지 로드
    ALLEGRO_BITMAP* background = al_load_bitmap("C:\\workspace\\hogwarts\\hachu-magic\\hachu-magic\\placeholder.jpeg");
    must_init(background, "background-image");

    ALLEGRO_BITMAP* player_img = al_load_bitmap("blue.jpeg");
    must_init(player_img, "player image");

    ALLEGRO_BITMAP* alien_img = al_load_bitmap("green.jpeg");
    must_init(alien_img, "alien image");

   /* ALLEGRO_BITMAP* alien_img = al_load_bitmap("mouse.png");
    must_init(alien_img, "alien image");*/

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");
    al_register_event_source(queue, al_get_display_event_source(disp));

    // player 중앙 고정
    player.x = SCREEN_W / 2;
    player.y = SCREEN_H / 2;

    // alien 초기화
    for (int i = 0; i < MAX_ALIENS; i++)
        aliens[i] = createAlien();

    // player/alien 크기 조정
    int player_w = 50; // 작은 크기로 조정
    int player_h = 50;
    int alien_w = 40;
    int alien_h = 40;

    bool done = false;
    while (!done) {
        ALLEGRO_EVENT event;
        while (al_get_next_event(queue, &event)) {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                done = true;
        }

        // alien 이동
        for (int i = 0; i < MAX_ALIENS; i++)
            moveAlien(&aliens[i]);

        // 배경 다시 그리기
        al_draw_scaled_bitmap(background, 0, 0,
            al_get_bitmap_width(background),
            al_get_bitmap_height(background),
            0, 0, SCREEN_W, SCREEN_H, 0);

        // player와 alien overlay (크기 조정)
        al_draw_scaled_bitmap(player_img, 0, 0,
            al_get_bitmap_width(player_img),
            al_get_bitmap_height(player_img),
            player.x - player_w / 2, player.y - player_h / 2,
            player_w, player_h, 0);

        for (int i = 0; i < MAX_ALIENS; i++)
            al_draw_scaled_bitmap(alien_img, 0, 0,
                al_get_bitmap_width(alien_img),
                al_get_bitmap_height(alien_img),
                aliens[i].x - alien_w / 2, aliens[i].y - alien_h / 2,
                alien_w, alien_h, 0);

        al_flip_display();
        al_rest(0.1); // 약 50FPS
    }

    al_destroy_bitmap(player_img);
    al_destroy_bitmap(alien_img);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}
#endif

/*speed로 해서 한건데, 지금 이거 안돌아감*/
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_ALIENS 10

// --- player와 alien 구조체 ---
typedef struct { float x, y; } Player;
typedef struct { float x, y; float speed; int pattern; } Alien;

Player player;
Alien aliens[MAX_ALIENS];

ALLEGRO_BITMAP* background = NULL;
ALLEGRO_BITMAP* player_img = NULL;
ALLEGRO_BITMAP* alien_img = NULL;


// --- alien 생성 ---
Alien createAlien() {
    Alien a;
    int side = rand() % 4;

    switch (side) {
    case 0: a.x = rand() % SCREEN_W; a.y = 0; break;
    case 1: a.x = rand() % SCREEN_W; a.y = SCREEN_H; break;
    case 2: a.x = 0; a.y = rand() % SCREEN_H; break;
    case 3: a.x = SCREEN_W; a.y = rand() % SCREEN_H; break;
    }

    a.speed = 1.5 + (rand() % 100) / 50.0; // 최소 1.5 ~ 3.5 정도
    a.pattern = rand() % 3;
    return a;
}

// --- alien 이동 ---
void moveAlien(Alien* a) {
    float dx = player.x - a->x;
    float dy = player.y - a->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist == 0) return;

    switch (a->pattern) {
    case 0: // 직선
        a->x += (dx / dist) * a->speed;
        a->y += (dy / dist) * a->speed;
        break;
    case 1: // 랜덤 지그재그
        a->x += (dx / dist) * a->speed + (rand() % 3 - 1);
        a->y += (dy / dist) * a->speed + (rand() % 3 - 1);
        break;
    case 2: // 사인 곡선 이동
        a->x += (dx / dist) * a->speed + sin(a->y * 0.05) * 2;
        a->y += (dy / dist) * a->speed;
        break;
    }
}

// --- 메인 ---
int main() {
    must_init(al_init(), "allegro");
    al_init_image_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(SCREEN_W, SCREEN_H);
    must_init(disp, "display");

    // --- 이미지 로드 ---
    background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background image");

    player_img = al_load_bitmap("blue.jpeg");
    must_init(player_img, "player image");

    alien_img = al_load_bitmap("green.jpeg");
    must_init(alien_img, "alien image");

    // --- player 중앙 고정 ---
    player.x = SCREEN_W / 2;
    player.y = SCREEN_H / 2;

    // --- alien 초기화 ---
    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i] = createAlien();
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_register_event_source(queue, al_get_display_event_source(disp));

    bool done = false;

    while (!done) {
        ALLEGRO_EVENT event;
        if (al_get_next_event(queue, &event)) {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                done = true;
        }

        // --- 이동 ---
        for (int i = 0; i < MAX_ALIENS; i++) {
            moveAlien(&aliens[i]);
        }

        // --- 그리기 ---
        al_draw_scaled_bitmap(background, 0, 0,
            al_get_bitmap_width(background),
            al_get_bitmap_height(background),
            0, 0, SCREEN_W, SCREEN_H, 0);

        int player_w = 50, player_h = 50;
        al_draw_scaled_bitmap(player_img, 0, 0,
            al_get_bitmap_width(player_img),
            al_get_bitmap_height(player_img),
            (int)(player.x - player_w / 2),
            (int)(player.y - player_h / 2),
            player_w, player_h, 0);

        int alien_w = 40, alien_h = 40;
        for (int i = 0; i < MAX_ALIENS; i++) {
            al_draw_scaled_bitmap(alien_img, 0, 0,
                al_get_bitmap_width(alien_img),
                al_get_bitmap_height(alien_img),
                (int)(aliens[i].x - alien_w / 2),
                (int)(aliens[i].y - alien_h / 2),
                alien_w, alien_h, 0);
        }

        al_flip_display();
        al_rest(0.01); // CPU 과부하 방지
    }

    // --- 리소스 해제 ---
    al_destroy_bitmap(background);
    al_destroy_bitmap(player_img);
    al_destroy_bitmap(alien_img);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}

#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

typedef struct {
    float x, y;
    float dx, dy;
    float speed;
    int alive;
} Alien;

void must_init(bool test, const char* description) {
    if (!test) {
        printf("couldn't initialize %s\n", description);
        exit(1);
    }
}

Alien createAlien(int stage, int width, int height) {
    Alien a;
    int side = rand() % 4;

    if (side == 0) { a.x = 0; a.y = rand() % height; }
    else if (side == 1) { a.x = width; a.y = rand() % height; }
    else if (side == 2) { a.x = rand() % width; a.y = 0; }
    else { a.x = rand() % width; a.y = height; }

    // 중앙 좌표 = player 위치
    float px = width / 2;
    float py = height / 2;

    float vx = px - a.x;
    float vy = py - a.y;
    float len = sqrt(vx * vx + vy * vy);

    if (stage == 1) a.speed = 2.0;
    else if (stage == 2) a.speed = 2.0;
    else a.speed = 3.5; // stage3는 더 빠름

    a.dx = (vx / len) * a.speed;
    a.dy = (vy / len) * a.speed;
    a.alive = 1;
    return a;
}

int getAlienCount(int stage) {
    if (stage == 1) return 5;
    if (stage == 2) return 10;
    return 12; // stage3는 속도↑, 개수도 조금↑
}

int main() {
    srand(time(NULL));
    must_init(al_init(), "allegro");
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
    must_init(disp, "display");

    // 이미지 로드
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background");
    ALLEGRO_BITMAP* player_img = al_load_bitmap("blue.jpeg");
    must_init(player_img, "player");
    ALLEGRO_BITMAP* alien_img = al_load_bitmap("green.jpeg");
    must_init(alien_img, "alien");

    // 폰트 로드
    ALLEGRO_FONT* font = al_load_ttf_font("arial.ttf", 24, 0);
    must_init(font, "font");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    must_init(timer, "timer");

    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    bool done = false;
    bool redraw = true;

    int stage = 1;
    double stageTimes[3] = { 0 };
    double stageStartTime = al_get_time();

    int alienCount = getAlienCount(stage);
    Alien aliens[50];
    for (int i = 0; i < alienCount; i++) {
        aliens[i] = createAlien(stage, 800, 600);
    }

    while (!done) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Alien 이동
            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    aliens[i].x += aliens[i].dx;
                    aliens[i].y += aliens[i].dy;

                    // Player 중앙 도달 시 제거 (충돌 대신 사라짐)
                    if (abs(aliens[i].x - 400) < 10 && abs(aliens[i].y - 300) < 10) {
                        aliens[i].alive = 0;
                    }
                }
            }

            // Stage 클리어 체크
            bool allDead = true;
            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    allDead = false;
                    break;
                }
            }

            if (allDead) {
                stageTimes[stage - 1] = al_get_time() - stageStartTime;
                stage++;
                if (stage > 3) {
                    // 게임 끝
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 100, ALLEGRO_ALIGN_CENTER, "=== GAME CLEAR ===");
                    for (int i = 0; i < 3; i++) {
                        al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 160 + i * 40, ALLEGRO_ALIGN_CENTER,
                            "Stage %d Time: %.2f sec", i + 1, stageTimes[i]);
                    }
                    al_draw_textf(font, al_map_rgb(255, 255, 0), 400, 300, ALLEGRO_ALIGN_CENTER,
                        "TOTAL: %.2f sec", stageTimes[0] + stageTimes[1] + stageTimes[2]);
                    al_flip_display();

                    // 끝나고 창 닫을 때까지 대기
                    bool wait = true;
                    while (wait) {
                        ALLEGRO_EVENT ev;
                        al_wait_for_event(queue, &ev);
                        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                            wait = false;
                        }
                    }
                    break;
                }
                else {
                    alienCount = getAlienCount(stage);
                    for (int i = 0; i < alienCount; i++) {
                        aliens[i] = createAlien(stage, 800, 600);
                    }
                    stageStartTime = al_get_time();
                }
            }

            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // 배경
            al_draw_scaled_bitmap(background, 0, 0,
                al_get_bitmap_width(background), al_get_bitmap_height(background),
                0, 0, 800, 600, 0);

            // Player (중앙 고정, 크기 축소)
            al_draw_scaled_bitmap(player_img, 0, 0,
                al_get_bitmap_width(player_img), al_get_bitmap_height(player_img),
                400 - 32, 300 - 32, 64, 64, 0);

            // Alien (살아있는 것만 표시, 크기 축소)
            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    al_draw_scaled_bitmap(alien_img, 0, 0,
                        al_get_bitmap_width(alien_img), al_get_bitmap_height(alien_img),
                        aliens[i].x, aliens[i].y, 48, 48, 0);
                }
            }

            // 현재 스테이지 표시
            al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "Stage: %d", stage);

            al_flip_display();
        }
    }

    al_destroy_bitmap(background);
    al_destroy_bitmap(player_img);
    al_destroy_bitmap(alien_img);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
#endif