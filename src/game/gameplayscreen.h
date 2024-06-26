#pragma once

#include <aether/aether.h>
#include <secs/secs.h>
#include <set>

#include "../core/gameworld.h"

#include "aether/graphics/camera.h"

#include "aether/graphics/topdownscroller.h"


class GameplayScreen : public aether::core::IScreen {
public:
	GameplayScreen();
    ~GameplayScreen() override = default;

	// IScreen interface
	int Load() override;
    void Update(uint64_t delta) override;
	void Render() override;
	int Unload() override;

private:

    aether::graphics::Camera::SharedPtr m_cam;
    aether::graphics::Camera::SharedPtr m_guiCam;

    std::shared_ptr<GameWorld> m_gameWorld;

    float m_scale = 4.f;

    bool m_pause = true;

    bool m_requestCloseApp = false;

	aether::graphics::TopDownMapScroller m_scroll;

    std::shared_ptr<aether::scene::Scene> m_scene;

    std::vector<std::string> m_contextControls;

};
