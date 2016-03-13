#pragma once

#include "../core/iscreen.h"
#include "../core/animation.h"
#include "../ai/pfmap.h"
#include "entity.h"
#include "player.h"

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
	void tilesRender();

private:
	Game* m_game;
	Player::SharedPtr m_player;
	Matrix2Di::SharedPtr m_map;
	Matrix2Di::SharedPtr m_tileMap;
	std::shared_ptr<NavigationMap> m_navmap;

};
