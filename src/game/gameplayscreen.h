#pragma once

#include "../core/iscreen.h"
#include "../core/animation.h"
#include "../ai/pfmap.h"
#include "entity.h"

class Game;

class GameplayScreen : public IScreen {
public:
	GameplayScreen(Game* g);
	virtual ~GameplayScreen();

	// IScreen interface
	void wake();
	void update(double delta);
	void render();

	void debugRender();

private:
	Game* m_game;
	Entity::SharedPtr m_player;
	Matrix2Di::SharedPtr m_map;
	std::shared_ptr<NavigationMap> m_navmap;

};
