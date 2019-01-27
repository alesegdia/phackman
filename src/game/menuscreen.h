#pragma once

#include <aether/aether.h>
#include <secs/secs.h>

#include "../core/gameworld.h"

#include <allegro5/allegro_ttf.h>

class PhackmanGame;

class MenuScreen : public aether::core::IScreen {
public:
    MenuScreen(PhackmanGame* g);
    ~MenuScreen() override = default;

	// IScreen interface
	void show() override;
    void update(uint64_t delta) override;
	void render() override;
	void hide() override;

private:
	PhackmanGame* m_game;
    Camera::SharedPtr m_cam;

};
