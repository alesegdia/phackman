#include "allegroapp.h"
#include <stdio.h>
#include <allegro5/allegro_image.h>

AllegroApp::AllegroApp( int screen_width, int screen_height )
	: m_screenWidth(screen_width), m_screenHeight(screen_height)
{

}

AllegroApp::~AllegroApp() {

}

int AllegroApp::Init() {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	m_timer = al_create_timer(1.0 / FPS);
	if(!m_timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	m_display = al_create_display(m_screenWidth, m_screenHeight);
	if(!m_display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(m_timer);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(m_display));

	m_eventQueue = al_create_event_queue();
	if(!m_eventQueue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(m_display);
		al_destroy_timer(m_timer);
		return -1;
	}

	al_register_event_source(m_eventQueue, al_get_display_event_source(m_display));
	al_register_event_source(m_eventQueue, al_get_timer_event_source(m_timer));
	al_register_event_source(m_eventQueue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));
	al_start_timer(m_timer);

	al_set_target_bitmap(al_get_backbuffer(m_display));
	ready();

	return 0;
}

void AllegroApp::handleEvent(ALLEGRO_EVENT& ev) {
	if(ev.type == ALLEGRO_EVENT_TIMER) {
		handleKeyInput();
		m_redraw = true;
	}
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		m_doexit = true;
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			case ALLEGRO_KEY_Q: 
				key[KEY_SLEFT] = true;
				break;

			case ALLEGRO_KEY_E:
				key[KEY_SRIGHT] = true;
				break;
		}
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			case ALLEGRO_KEY_ESCAPE:
				m_doexit = true;
				break;

			case ALLEGRO_KEY_Q:
				key[KEY_SLEFT] = false;
				break;

			case ALLEGRO_KEY_E:
				key[KEY_SRIGHT] = false;
				break;
		}
	}
}

ALLEGRO_DISPLAY *AllegroApp::display()
{
	return m_display;
}

int AllegroApp::Exec() {
	int retcode = Init();
	if( retcode != 0 ) return retcode;

	double now, then;
	now = then = al_get_time();

	while(!m_doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(m_eventQueue, &ev);
		handleEvent(ev);

		now = al_get_time();
		double delta = now - then;
		then = now;

		update(delta);

		if( m_redraw && al_is_event_queue_empty(m_eventQueue) ) {
			al_set_target_bitmap(al_get_backbuffer(m_display));
			m_redraw = false;
			draw();
			al_flip_display();
		}
	}

}


