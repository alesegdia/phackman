#include "gameplayscreen.h"
#include "game.h"
#include "assets.h"

#include <allegro5/allegro.h>

GameplayScreen::GameplayScreen( Game* g )
{
	m_game = g;
}

GameplayScreen::~GameplayScreen()
{

}

void GameplayScreen::wake()
{
}

void GameplayScreen::update(double delta)
{

}

void GameplayScreen::render()
{
	al_clear_to_color(al_map_rgb(20,20,20));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	al_draw_bitmap(Assets::instance->characterSheet, 0, 0, 0);
}
