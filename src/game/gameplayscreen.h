#pragma once

#include <alligator/game/iscreen.h>
#include <alligator/util/matrix.h>
#include <alligator/camera/camera.h>
#include <secs/secs.h>

#include "../ai/pfmap.h"
#include "../ecs/world.h"
#include "../map/mapscene.h"

#include <allegro5/allegro_ttf.h>

class PhackmanGame;

class GameplayScreen : public IScreen {
public:
	GameplayScreen(PhackmanGame* g);
    ~GameplayScreen() override = default;

	// IScreen interface
	void show() override;
	void update(double delta) override;
	void render() override;
	void hide() override;

private:
	PhackmanGame* m_game;

    MapScene m_mapScene;

    Camera::SharedPtr m_cam;
    Camera::SharedPtr m_guiCam;

    secs::Entity m_playerEntity;

	GameWorld gw;

    int m_scale = 2;

    bool m_pause = false;

};
