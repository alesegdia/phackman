#include "game.h"

Game::Game(int sw, int sh)
	: AllegroApp( sw, sh )
{

}

Game::~Game()
{

}

void Game::ready() {
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(m_display));

	// init first screen
}

void Game::handleKeyInput() {
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

void Game::draw() {
	al_clear_to_color(al_map_rgb(255,0,255));
	al_set_target_bitmap(al_get_backbuffer(m_display));
}
