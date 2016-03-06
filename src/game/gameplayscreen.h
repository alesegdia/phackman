#pragma once

#include "../core/iscreen.h"
#include "../core/animation.h"

class Game;

class GameplayScreen : public IScreen {
public:
	GameplayScreen(Game* g);
	virtual ~GameplayScreen();

	// IScreen interface
	void wake();
	void update(double delta);
	void render();

private:
	Game* m_game;
	AnimationData ad;

};
