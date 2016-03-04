
#pragma once

#include "../app/allegroapp.h"
#include <allegro5/allegro.h>

class Game : public AllegroApp {

public:

	Game ( int sw, int sh )
		: AllegroApp( sw, sh )
	{

	}

	virtual ~Game() {}

	void Ready() {
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_set_target_bitmap(al_get_backbuffer(display));
	}

	void HandleKeyInput() {
		if(key[KEY_UP]) {
		}

		if(key[KEY_DOWN] ) {
		}

		if(key[KEY_LEFT]) {
		}

		if(key[KEY_RIGHT] ) {
		}

		if(key[KEY_SLEFT]) {
		}

		if( key[KEY_SRIGHT] ) {
		}
	}

	void Draw() {
		al_clear_to_color(al_map_rgb(255,0,255));
		al_set_target_bitmap(al_get_backbuffer(display));
	}

};

