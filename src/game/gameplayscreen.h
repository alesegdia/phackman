#pragma once

#include <alligator/game/iscreen.h>
#include <alligator/util/matrix.h>
#include <alligator/camera/camera.h>
#include <secs/secs.h>

#include "../ai/pfmap.h"
#include "../ecs/world.h"

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

	Matrix2Di::SharedPtr m_map;
	Matrix2Di::SharedPtr m_tileMap;
	std::shared_ptr<NavigationMap> m_navmap;

    bool m_shownodes = false;
    bool m_showsolid = false;

    Camera::SharedPtr m_cam;

    TransformComponent* m_playerTransformComponent;

	GameWorld gw;

};
