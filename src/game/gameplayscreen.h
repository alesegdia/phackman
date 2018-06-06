#pragma once

#include <alligator/game/iscreen.h>
#include <alligator/util/matrix.h>
#include <alligator/camera/camera.h>
#include <secs/secs.h>

#include "../ai/pfmap.h"
#include "../ecs/world.h"
#include "../map/mapscene.h"

class PhackmanGame;

class GameplayScreen : public IScreen {
public:
	GameplayScreen(PhackmanGame* g);
	virtual ~GameplayScreen();

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override;
	void hide() override;

	void debugRender();
	void tilesRender();

private:
	PhackmanGame* m_game;

    MapScene m_mapScene;
    bool m_shownodes = false;
    bool m_showsolid = false;

    Camera::SharedPtr m_cam;
    Camera::SharedPtr m_guiCam;

    secs::Entity m_playerEntity;

	GameWorld gw;

};
