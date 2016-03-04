
#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include "../core/allegroapp.h"
#include "../core/iscreen.h"

class Game : public AllegroApp {

public:

	Game ( int sw, int sh );
	virtual ~Game();

	void ready();
	void handleKeyInput();
	void draw();

	std::shared_ptr<IScreen> m_currentScreen;

};

