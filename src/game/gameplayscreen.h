#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

#include "../core/gameworld.h"

#include <allegro5/allegro_ttf.h>

class PhackmanGame;

class GameplayScreen : public aether::core::IScreen {
public:
	GameplayScreen(PhackmanGame* g);
    ~GameplayScreen() override = default;

	// IScreen interface
	void show() override;
    void update(uint64_t delta) override;
	void render() override;
	void hide() override;

private:
	PhackmanGame* m_game;

    Camera::SharedPtr m_cam;
    Camera::SharedPtr m_guiCam;

    std::shared_ptr<GameWorld> gw;

    float m_scale = 2.f;

    bool m_pause = true;

};
