#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

int setup_allegro(ALLEGRO_DISPLAY**,ALLEGRO_EVENT_QUEUE**);
void setup_event_sources(ALLEGRO_EVENT_QUEUE*,ALLEGRO_DISPLAY*);
void setup_timer_event_sources(ALLEGRO_TIMER*);
int setup_game_timers(ALLEGRO_TIMER**);
void init_allegro();
void shutdown_allegro();

ALLEGRO_BITMAP* load_bitmap(char[3],char[100]);

#endif // MAIN_H_INCLUDED
