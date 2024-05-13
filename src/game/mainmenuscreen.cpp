#include "mainmenuscreen.h"

#include "assets.h"
#include "../constants.h"
#include <filesystem>

#include "gameplayscreen.h"


MainMenuScreen::MainMenuScreen()
	: m_cam(
		new aether::graphics::Camera(
			{ Constants::WindowWidth, Constants::WindowHeight }))
{

}

int MainMenuScreen::Load()
{
	return 0;
}

void MainMenuScreen::Update(uint64_t delta)
{
	if (aether::core::is_key_down(aether::core::KeyCode::Escape))
	{
		RequestCloseApp();
	}

	if(aether::core::is_key_just_pressed(aether::core::KeyCode::Space))
	{
		std::shared_ptr<GameplayScreen> gameplayScreen = std::make_shared<GameplayScreen>();
		GoToScreen(gameplayScreen);
	}

}

void MainMenuScreen::Render()
{
	aether::graphics::clear(0.f, 0.f, 0.f);

	m_cam->SetPosition(0, 0);
	m_cam->SetScale(1.f, 1.f);
	m_cam->Bind();
	Assets::instance->mainMenuScreenBitmap.Draw(-1920/2, -1080/2);

	m_cam->SetPosition(0, 0);
	m_cam->SetScale(4.f, 4.f);
	m_cam->Bind();
	//int offx = 110;
	//int offy = -50;
	int offx = 0;
	int offy = 0;
	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_super.font")->Print(
		"Phackman", offx + 0, offy - 50,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);
	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_big.font")->Print(
		"Press SPACE to start", offx + 0, offy + 20,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);
}

int MainMenuScreen::Unload()
{
	return 0;
}


