#include <allegro5/allegro.h>
#include <allegro5/keyboard.h>
//#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <time.h>

#include "main.h"

char drive[3] = "f:";
ALLEGRO_EVENT_QUEUE *eventQueue=NULL;
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *gameTimer;

int main(){
    int carry_on=setup_allegro(&display,&eventQueue);   // sets up display dimensions, installs keyboard, initiates random #'s and creates event_queue
    if (!carry_on==0) {
        return -1;
    }

    carry_on=setup_game_timers(&gameTimer);

    if(!carry_on==0){
        al_destroy_display(display);
        al_destroy_event_queue(eventQueue);
        return -1;
    }

    setup_event_sources(eventQueue,display); // sets up display, keyboard
    setup_timer_event_sources(gameTimer); // sets up any passed timer event sources...

    init_allegro(); // calls all al_init* functions

    // ====================================
    // = MAIN BODY OF GAME LOOP GOES HERE =
    // ====================================
    al_start_timer(gameTimer);
    al_clear_to_color(al_map_rgb(128,0,0));

    bool done=false;
    bool redraw=false;
    ALLEGRO_EVENT ev;

    while (!done)
    {
        redraw=false;
        al_wait_for_event(eventQueue,&ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ESCAPE:
                done=true;
                break;
            case ALLEGRO_KEY_UP:
                al_clear_to_color(al_map_rgb(128,128,128));
                break;
            }
        }

        if(ev.type==ALLEGRO_EVENT_DISPLAY_CLOSE) { // clicking the x closes the window.
            done=true;
        }

        if(ev.type==ALLEGRO_EVENT_TIMER){
            if(ev.timer.source==gameTimer){
                redraw = true; // time for next frame
            }
        }

        if(redraw){
            al_flip_display();
        }
    }

    al_rest(2.0);

    // ====================================
    // = MAIN BODY OF GAME LOOP ENDS HERE =
    // ====================================

    shutdown_allegro(); // // calls all al_shutdown* functions - should mirror the init_allegro methods...

    al_destroy_timer(gameTimer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);

    return 0;
}

int setup_allegro(ALLEGRO_DISPLAY** display,ALLEGRO_EVENT_QUEUE** eventQueue){
    srand((unsigned)time(NULL));
    if(!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if(!al_install_keyboard())
    {
        fprintf(stderr,"Failed to install keyboard.");
        return -1;
    }

    al_set_new_display_option(ALLEGRO_COLOR_SIZE,32,ALLEGRO_REQUIRE);  // not sure this is working... // color depth???

    *display=al_create_display(640, 480);  // think of * as value of and & as address of
    if(!*display){
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    *eventQueue=al_create_event_queue();
    if(*eventQueue==NULL){
        al_destroy_display(*display);  // deference display since it is a pointer to a pointer. * = value of) al_destroy_display takes a allegro_display pointer as a parameter
        fprintf(stderr,"Failed to create the event queue.");
        return -1;
    }

    return 0;
}

void setup_event_sources(ALLEGRO_EVENT_QUEUE* eventQueue,ALLEGRO_DISPLAY* display){
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
}

void setup_timer_event_sources(ALLEGRO_TIMER* gameTimer){
    al_register_event_source(eventQueue, al_get_timer_event_source(gameTimer));
}

int setup_game_timers(ALLEGRO_TIMER** gameTimer){
    *gameTimer=al_create_timer(1.0/30.0); // set the FPS - 1/3 here will not work - that makes a 0.
    if (!*gameTimer){
        fprintf(stderr,"Failed to create gameTimer.");
        return -1;
    }

    return 0;
}

void init_allegro(){
//    al_init_primitives_addon();
//    al_init_image_addon();
//    al_init_font_addon();
//    al_init_ttf_addon();
}

void shutdown_allegro(){
//    al_shutdown_primitives_addon();
//    al_shutdown_image_addon();
//    al_shutdown_font_addon();
//    al_shutdown_ttf_addon();
}

ALLEGRO_BITMAP* load_bitmap(char drv[3],char fn[100]){
    char workFN[110];

    strcpy(workFN,drive);
    strcat(workFN,fn);
    return al_load_bitmap(workFN);
}


