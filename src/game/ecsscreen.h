#pragma once

#include <alligator/game/iscreen.h>
#include <alligator/util/matrix.h>
#include <secs/secs.h>

#include "../ai/pfmap.h"
#include "entity.h"
#include "player.h"

class PhackmanGame;

class ECSScreen : public IScreen {
public:
	ECSScreen(PhackmanGame* g);
	virtual ~ECSScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override;
	void hide() override;

	void debugRender();
	void tilesRender();

private:
	PhackmanGame* m_game;

	Matrix2Di::SharedPtr m_map;
	Matrix2Di::SharedPtr m_tileMap;
	std::shared_ptr<NavigationMap> m_navmap;
	secs::Engine m_world;

};
