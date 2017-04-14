#include "phackmangame.h"
#include "assets.h"

PhackmanGame::PhackmanGame(int sw, int sh)
	: Game( sw, sh )
{
    this->setRenderFPS(64);
    this->setUpdateFPS(64);
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
