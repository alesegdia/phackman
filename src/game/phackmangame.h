
#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include <alligator/game/game.h>

#include "gameplayscreen.h"

class PhackmanGame : public Game {

public:

	PhackmanGame ( int sw, int sh );
	virtual ~PhackmanGame();

	int create( int argc, char** argv ) override ;
	void dispose() override ;

	// all screens
	std::shared_ptr<GameplayScreen> m_gameplayScreen;

};

