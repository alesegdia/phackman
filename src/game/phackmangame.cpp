#include "phackmangame.h"
#include "assets.h"

PhackmanGame::PhackmanGame(int sw, int sh)
    : aether::core::Application( sw, sh )
{

}

PhackmanGame::~PhackmanGame()
{

}

int PhackmanGame::ready(int argc, char **argv)
{
    (void)argc;
    (void)argv;
	Assets::Initialize();

	m_gameplayScreen.reset(new GameplayScreen(this));

    setScreen(m_gameplayScreen.get());

	return 0;
}

void PhackmanGame::dispose()
{
	Assets::Dispose();
}
