#include "assets.h"
#include <iostream>

namespace {
    constexpr uint64_t STATIC_DURATION = 5e6;
    constexpr uint64_t PHACKMAN_WALK_DURATION = 0.1e6;
    constexpr uint64_t PHACKMAN_ATTACK_DURATION = 0.1e6;
}

Assets* Assets::instance = nullptr;

Assets::Assets()
{
    assetsManager.LoadFolder("assets/");

    maptilesSheet = assetsManager.GetAsset<aether::graphics::Spritesheet>("maptiles.sheet");

    enemyBitmap.Load("assets/enemysheet.png");
    enemySheet.reset(new aether::graphics::Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap.Load("assets/turrets.png");
    buildingsSheet.reset(new aether::graphics::Spritesheet(4, 2, buildingsBitmap));

    mainMenuScreenBitmap.Load("assets/mainScreen1920.png");
    elevatorBGBitmap.Load("assets/elevatorScreen1920_BG.png");
    elevatorDudeBitmap.Load("assets/elevatorScreen1920_DUDE.png");

    industryNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    industryNode->AddFrame(*maptilesSheet->GetFrame(72));

    powerNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    powerNode->AddFrame(*maptilesSheet->GetFrame(73));

    turretStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretStand->AddFrame(*buildingsSheet->GetFrame(0));

    turretBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretBullet->AddFrame(*buildingsSheet->GetFrame(1));

    spawnerStand = assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("spawner.json")->anims["SpawnerStand"];

    guiFont = assetsManager.GetAsset<aether::graphics::Font>("bitcell_big.font");

    // mainTheme.reset(new aether::audio::Stream());
    // mainTheme->Load("phackman-theme.mp3");

    // mainTheme->Play();
}

Assets::~Assets()
{
    enemyBitmap.Destroy();
    buildingsBitmap.Destroy();
    guiFont->Destroy();
}

void Assets::Initialize()
{
    Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}


