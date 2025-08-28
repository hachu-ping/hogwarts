#if 0
#include <stdio.h>

int main(void) {
	printf("Hello");
	return 0;
}
#endif

#if 1
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

#include "utils.h"

#define SCREEN_W 800
#define SCREEN_H 600
#define MAX_ALIENS 5

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

    //printf("%d %f %f %f\n", dx, dist, a->speed, dx / dist * a->speed);
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


#if 0
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

typedef struct { int x, y; } Player;
typedef struct { int x, y; float speed; bool alive; } Alien;

Player player;
Alien aliens[MAX_ALIENS];

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* background;
ALLEGRO_BITMAP* player_img;
ALLEGRO_BITMAP* alien_img;

// Alien 생성
Alien createAlien() {
    Alien a;
    a.speed = 2.0;
    a.alive = true;
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
    if (!a->alive) return;
    int dx = player.x - a->x;
    int dy = player.y - a->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist < 1.0) return;
    a->x += (int)(dx / dist * a->speed);
    a->y += (int)(dy / dist * a->speed);
}

// 한 스테이지 실행 (alienCount마리 × 3wave)
void runStage(int alienCount, ALLEGRO_EVENT_QUEUE* queue) {
    for (int wave = 1; wave <= 3; wave++) {
        // wave마다 alienCount마리만 생성
        for (int i = 0; i < alienCount; i++) {
            aliens[i] = createAlien();
        }

        bool wave_done = false;
        while (!wave_done) {
            ALLEGRO_EVENT event;
            while (al_get_next_event(queue, &event)) {
                if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                    return;
            }

            // alien 이동
            for (int i = 0; i < alienCount; i++) {
                moveAlien(&aliens[i]);
            }

            // 배경 그리기
            al_draw_scaled_bitmap(background, 0, 0,
                al_get_bitmap_width(background),
                al_get_bitmap_height(background),
                0, 0, SCREEN_W, SCREEN_H, 0);

            // player 그리기
            al_draw_scaled_bitmap(player_img, 0, 0,
                al_get_bitmap_width(player_img),
                al_get_bitmap_height(player_img),
                player.x - 25, player.y - 25,
                50, 50, 0);

            // alien 그리기
            for (int i = 0; i < alienCount; i++) {
                if (aliens[i].alive) {
                    al_draw_scaled_bitmap(alien_img, 0, 0,
                        al_get_bitmap_width(alien_img),
                        al_get_bitmap_height(alien_img),
                        aliens[i].x - 20, aliens[i].y - 20,
                        40, 40, 0);
                }
            }

            al_flip_display();
            al_rest(0.02);

            // 모두 중앙 도착했는지 체크
            bool all_arrived = true;
            for (int i = 0; i < alienCount; i++) {
                int dx = player.x - aliens[i].x;
                int dy = player.y - aliens[i].y;
                float dist = sqrt(dx * dx + dy * dy);
                if (dist > 10) { // 아직 도착 안 한 애가 있음
                    all_arrived = false;
                    break;
                }
            }

            if (all_arrived) {
                // 동시에 사라지게
                for (int i = 0; i < alienCount; i++)
                    aliens[i].alive = false;
                wave_done = true;
            }
        }

        // wave 끝 → 잠깐 쉬기
        al_clear_to_color(al_map_rgb(0, 0, 0));
        al_flip_display();
        al_rest(0.5);
    }
}

int main() {
    srand(time(NULL));

    al_init();
    al_init_image_addon();

    disp = al_create_display(SCREEN_W, SCREEN_H);
    background = al_load_bitmap("C:\\workspace\\hogwarts\\hachu-magic\\hachu-magic\\placeholder.jpeg");
    player_img = al_load_bitmap("C:\\workspace\\hogwarts\\hachu-magic\\hachu-magic\\blue.jpeg");
    alien_img = al_load_bitmap("C:\\workspace\\hogwarts\\hachu-magic\\hachu-magic\\green.jpeg");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(disp));

    // player 중앙 고정
    player.x = SCREEN_W / 2;
    player.y = SCREEN_H / 2;

    // Stage 진행
    runStage(5, queue); // Stage 1: 5마리 × 3 wave
    runStage(7, queue); // Stage 2: 7마리 × 3 wave
    runStage(9, queue); // Stage 3: 9마리 × 3 wave

    // 끝나면 2초 유지
    al_rest(2.0);

    al_destroy_bitmap(player_img);
    al_destroy_bitmap(alien_img);
    al_destroy_bitmap(background);
    al_destroy_display(disp);
    al_destroy_event_queue(queue);

    return 0;
}

#endif

//5마리만 나오게 하고 있는데 잘 안도기ㅗ 15마리가 먼저 나오네....
#if 0
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
typedef struct { int x, y; float speed; int pattern; bool alive; } Alien;

Player player;
Alien aliens[MAX_ALIENS];

void must_init(bool test, const char* description) {
    if (test) return;
    fprintf(stderr, "Failed to initialize %s\n", description);
    exit(1);
}

Alien createAlien() {
    Alien a;
    a.speed = 2 + (rand() % 100) / 50.0;
    a.pattern = rand() % 3;
    a.alive = true;
    int side = rand() % 4;
    switch (side) {
    case 0: a.x = -50; a.y = rand() % SCREEN_H; break;
    case 1: a.x = SCREEN_W + 50; a.y = rand() % SCREEN_H; break;
    case 2: a.x = rand() % SCREEN_W; a.y = -50; break;
    case 3: a.x = rand() % SCREEN_W; a.y = SCREEN_H + 50; break;
    }
    return a;
}

bool moveAlien(Alien* a) {
    if (!a->alive) return false;
    int dx = player.x - a->x, dy = player.y - a->y;
    float dist = sqrt(dx * dx + dy * dy);
    if (dist == 0) return false;
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
    if (dist < 20) {
        a->alive = false;
        printf("[DEBUG] Alien at (%d,%d) destroyed.\n", a->x, a->y);
        return true;
    }
    return false;
}

int main() {
    srand(time(NULL


#endif

#if 0
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
    void moveAlien(Alien * a) {
        int dx = player.x - a->x;
        int dy = player.y - a->y;
        float dist = sqrt(dx * dx + dy * dy);
        if (dist == 0) { return; }


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

        /*ALLEGRO_BITMAP* alien_img = al_load_bitmap("green.jpeg");
        must_init(alien_img, "alien image");*/

        ALLEGRO_BITMAP* alien_img = al_load_bitmap("mouse.png");
        must_init(alien_img, "alien image");

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
            al_rest(0.02); // 약 50FPS
        }

        al_destroy_bitmap(player_img);
        al_destroy_bitmap(alien_img);
        al_destroy_bitmap(background);
        al_destroy_display(disp);
        al_destroy_event_queue(queue);

        return 0;
    }
#endif