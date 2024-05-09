#pragma once

#include <aether/aether.h>


class MainMenuScreen : public aether::core::IScreen {
public:
	MainMenuScreen();
	~MainMenuScreen() override = default;

	// IScreen interface
	int Load() override;
	void Update(uint64_t delta) override;
	void Render() override;
	int Unload() override;

private:
	aether::graphics::Camera::SharedPtr m_cam;

};
