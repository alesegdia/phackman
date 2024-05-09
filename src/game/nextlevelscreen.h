#pragma once

#include <aether/aether.h>


class NextLevelScreen : public aether::core::IScreen {
public:
    NextLevelScreen();
    ~NextLevelScreen() override = default;

	// IScreen interface
	int Load() override;
    void Update(uint64_t delta) override;
	void Render() override;
	int Unload() override;

private:

    aether::graphics::Camera::SharedPtr m_cam;
	float m_playerPos = 0;
	float m_bgPos = 0;

};
