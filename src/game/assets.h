#pragma once

#include <memory>
#include <aether/aether.h>

#include "aether/resources/AssetsManager.h"


class Assets
{
public:

	// singleton interface
	static Assets* instance;
	static void Initialize();
	static void Dispose();

	Assets();
	~Assets();

    aether::graphics::Texture enemyBitmap;
    aether::graphics::Texture buildingsBitmap;


    aether::graphics::Texture mainMenuScreenBitmap;
    aether::graphics::Texture elevatorBGBitmap;
    aether::graphics::Texture elevatorDudeBitmap;

    std::shared_ptr<aether::graphics::Spritesheet> enemySheet;
    std::shared_ptr<aether::graphics::Spritesheet> buildingsSheet;
    std::shared_ptr<aether::graphics::Spritesheet> maptilesSheet;

    std::shared_ptr<aether::graphics::Animation> industryNode;
    std::shared_ptr<aether::graphics::Animation> powerNode;

    std::shared_ptr<aether::graphics::Animation> turretBullet;

    std::shared_ptr<aether::graphics::Animation> spawnerStand;
    std::shared_ptr<aether::graphics::Animation> turretStand;

    std::shared_ptr<aether::graphics::Font> guiFont;

    //std::shared_ptr<aether::audio::Stream> mainTheme;

    aether::resources::AssetsManager assetsManager;



};
