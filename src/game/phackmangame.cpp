#include "phackmangame.h"
#include "assets.h"

PhackmanGame::PhackmanGame(int sw, int sh)
	: Game( sw, sh )
{

}

PhackmanGame::~PhackmanGame()
{

}

void PhackmanGame::create()
{
	Assets::Initialize();

	m_gameplayScreen.reset(new GameplayScreen(this));

	setScreen(m_gameplayScreen);
}

void PhackmanGame::dispose()
{
	Assets::Dispose();
}
