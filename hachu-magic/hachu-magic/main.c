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
   
    al_draw_bitmap(background, 0, 0, 0);
    //al_draw_scaled_bitmap(background, 0, 0, 900, 600, 0, 0, 800, 600, 0);
 
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