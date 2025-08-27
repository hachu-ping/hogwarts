#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "initializer.h"
#include "utils.h"


int main() {
    // 알레그로 초기화
    init_allegro();

    // 에드온 초기화
    init_addons();
    install_driver();

    // 리소스 초기화
    ALLEGRO_TIMER* timer = init_timer(1.0 / 60.0);
    ALLEGRO_DISPLAY* disp = init_display(1400, 800);
    ALLEGRO_EVENT_QUEUE* queue = init_event_queue();


    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_keyboard_event_source());


    // load placeholder image
    ALLEGRO_BITMAP* background = al_load_bitmap("placeholder.jpeg");
    must_init(background, "background-image");
   
    al_draw_scaled_bitmap(background, 0, 0, 640, 437, 0, 0, 800, 600, 0);
 

    printf("RESOURCE INITIALZ\n");
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