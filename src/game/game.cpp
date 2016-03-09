#include "game.h"
#include "assets.h"

Game::Game(int sw, int sh)
	: AllegroApp( sw, sh )
{

}

Game::~Game()
{

}

void Game::ready()
{
	Assets::Initialize();

	m_gameplayScreen.reset(new GameplayScreen(this));
	m_currentScreen = m_gameplayScreen;
	m_currentScreen->wake();
}

void Game::draw()
{
	m_currentScreen->render();
}

void Game::update(double delta)
{
	m_currentScreen->update(delta);
}

void Game::dispose()
{
	Assets::Dispose();
}

void Game::close()
{
	m_doexit = true;
}
