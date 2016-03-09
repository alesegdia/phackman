
#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include "../core/allegroapp.h"
#include "../core/iscreen.h"

#include "gameplayscreen.h"

class Game : public AllegroApp {

public:

	Game ( int sw, int sh );
	virtual ~Game();

	void ready();
	void draw();
	void update(double delta);

	// all screens
	std::shared_ptr<GameplayScreen> m_gameplayScreen;

	// current screen
	std::shared_ptr<IScreen> m_currentScreen;

};

