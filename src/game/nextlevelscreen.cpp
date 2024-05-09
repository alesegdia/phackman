#include "nextlevelscreen.h"

#include "assets.h"
#include "../constants.h"
#include <filesystem>

#include "gameplayscreen.h"

//#include "../debug/mapsoliddebug.h"

NextLevelScreen::NextLevelScreen()
    : m_cam(
		new aether::graphics::Camera(
			{Constants::WindowWidth, Constants::WindowHeight}))
{

}

int NextLevelScreen::Load()
{

    return 0;
}

void NextLevelScreen::Update(uint64_t delta)
{
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
	{
        RequestCloseApp();
	}

	if (aether::core::is_key_just_pressed(aether::core::KeyCode::Space))
	{
		std::shared_ptr<GameplayScreen> gameplayScreen = std::make_shared<GameplayScreen>();
		GoToScreen(gameplayScreen);
	}

	m_playerPos += 0.3f;
	m_bgPos += 0.3f;
}

void NextLevelScreen::Render()
{
	aether::graphics::clear(0.f, 0.f, 0.f);

	m_cam->SetPosition(0, 0);
	m_cam->SetScale(2.f, 2.f);
	m_cam->Bind();

	{
		float shakeX = rand() % 100 / 50.f;
		float shakeY = rand() % 100 / 50.f;
		Assets::instance->elevatorBGBitmap.Draw(-1920 / 2 - m_bgPos * 0.1f + shakeX, shakeY + -1080 / 2 + m_bgPos);
	}

	{
		float shakeX = rand() % 100 / 50.f;
		float shakeY = rand() % 100 / 25.f;
		Assets::instance->elevatorDudeBitmap.Draw(m_playerPos * 0.1f + -1920 / 2 + shakeX, 300 + shakeY + -m_playerPos + -1080 / 2);
	}

	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_super.font")->Print(
		"Level Cleared", 0, -50,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);
	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_big.font")->Print(
		"Press SPACE for next level", 0, 20,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);




}

int NextLevelScreen::Unload()
{
	return 0;
}


