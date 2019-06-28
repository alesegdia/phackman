
#pragma once

#include <allegro5/allegro.h>
#include <memory>

#include <aether/aether.h>

#include "gameplayscreen.h"

class PhackmanGame : public aether::core::Application {

public:

	PhackmanGame ( int sw, int sh );
    virtual ~PhackmanGame() override;

    int ready( int argc, char** argv ) override ;
	void dispose() override ;

	// all screens
	std::shared_ptr<GameplayScreen> m_gameplayScreen;

};

