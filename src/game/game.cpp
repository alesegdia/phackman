#include "game.h"

Game::Game(int sw, int sh)
	: AllegroApp( sw, sh )
{

}

Game::~Game()
{

}

void Game::ready()
{
	m_gameplayScreen.reset(new GameplayScreen(this));
	m_currentScreen = m_gameplayScreen;
	m_currentScreen->wake();
}

void Game::handleKeyInput()
{
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

void Game::draw()
{
	m_currentScreen->render();
}

void Game::update(double delta)
{
	m_currentScreen->update(delta);
}
