#include "youdiescreen.h"

#include "assets.h"
#include "../constants.h"
#include <filesystem>

#include "mainmenuscreen.h"

//#include "../debug/mapsoliddebug.h"

#include "../core/persistentdata.h"

YouDieScreen::YouDieScreen()
    : m_cam(
		new aether::graphics::Camera(
			{Constants::WindowWidth, Constants::WindowHeight}))
{

}

int YouDieScreen::Load()
{
	PersistentData::Instance.Reset();
    return 0;
}

void YouDieScreen::Update(uint64_t delta)
{
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
	{
        RequestCloseApp();
	}

	if (aether::core::is_key_just_pressed(aether::core::KeyCode::Space))
	{
		std::shared_ptr<MainMenuScreen> mainScreen = std::make_shared<MainMenuScreen>();
		GoToScreen(mainScreen);
	}
}

void YouDieScreen::Render()
{
	aether::graphics::clear(0.f, 0.f, 0.f);

	m_cam->SetPosition(0, 0);
	m_cam->SetScale(4.f, 4.f);
	m_cam->Bind();

	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_super.font")->Print(
		"YOU DIED", 0, -50,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);
	Assets::instance->assetsManager.GetAsset<aether::graphics::Font>("bitcell_big.font")->Print(
		"Press SPACE to return to main menu", 0, 20,
		aether::graphics::Color::White, aether::graphics::TextAlign::Center);




}

int YouDieScreen::Unload()
{
	return 0;
}


