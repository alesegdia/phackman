#include "phackmangame.h"
#include "assets.h"

PhackmanGame::PhackmanGame(int sw, int sh)
	: Game( sw, sh )
{
    this->setRenderFPS(16);
    this->setUpdateFPS(32);
}

PhackmanGame::~PhackmanGame()
{

}

int PhackmanGame::create(int argc, char **argv)
{
	Assets::Initialize();

	m_gameplayScreen.reset(new GameplayScreen(this));

	setScreen(m_gameplayScreen);

	return 0;
}

void PhackmanGame::dispose()
{
	Assets::Dispose();
}
