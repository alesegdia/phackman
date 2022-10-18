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
    // SPRITESHEETS
    characterBitmap.Load("assets/phakman-sheet.png");
    characterSheet.reset(new aether::graphics::Spritesheet(3, 5, characterBitmap));

    maptilesBitmap.Load("assets/maptiles.png");
    maptilesSheet.reset(new aether::graphics::Spritesheet(6, 15, maptilesBitmap));

    enemyBitmap.Load("assets/enemysheet.png");
    enemySheet.reset(new aether::graphics::Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap.Load("assets/turrets.png");
    buildingsSheet.reset(new aether::graphics::Spritesheet(4, 2, buildingsBitmap));

    // ANIMATIONS
    phackmanWalk.reset(new aether::graphics::Animation(PHACKMAN_WALK_DURATION));
	phackmanWalk->AddFrame(*characterSheet->GetFrame(0));
	phackmanWalk->AddFrame(*characterSheet->GetFrame(1));
	phackmanWalk->AddFrame(*characterSheet->GetFrame(2));
	phackmanWalk->AddFrame(*characterSheet->GetFrame(3));

    phackmanStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    phackmanStand->AddFrame(*characterSheet->GetFrame(1));

    industryNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    industryNode->AddFrame(*maptilesSheet->GetFrame(30));

    powerNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    powerNode->AddFrame(*maptilesSheet->GetFrame(31));

    lsBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    lsBullet->AddFrame(*characterSheet->GetFrame(11));

    turretStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretStand->AddFrame(*buildingsSheet->GetFrame(0));

    turretBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretBullet->AddFrame(*buildingsSheet->GetFrame(1));

    phackmanAttack.reset(new aether::graphics::Animation(PHACKMAN_ATTACK_DURATION));
    phackmanAttack->AddFrame(*characterSheet->GetFrame(9));
    phackmanAttack->AddFrame(*characterSheet->GetFrame(8));

    slimeWalk.reset(new aether::graphics::Animation(STATIC_DURATION));
    slimeWalk->AddFrame(*characterSheet->GetFrame(10));

    spawnerStand.reset(new aether::graphics::Animation(0.25e6));
    spawnerStand->AddFrame(*enemySheet->GetFrame(0));
    spawnerStand->AddFrame(*enemySheet->GetFrame(0));
    spawnerStand->AddFrame(*enemySheet->GetFrame(0));
    spawnerStand->AddFrame(*enemySheet->GetFrame(0));
    spawnerStand->AddFrame(*enemySheet->GetFrame(1));
    spawnerStand->AddFrame(*enemySheet->GetFrame(1));
    spawnerStand->AddFrame(*enemySheet->GetFrame(1));
    spawnerStand->AddFrame(*enemySheet->GetFrame(1));
    spawnerStand->AddFrame(*enemySheet->GetFrame(3));
    spawnerStand->AddFrame(*enemySheet->GetFrame(3));
    spawnerStand->AddFrame(*enemySheet->GetFrame(3));
    spawnerStand->AddFrame(*enemySheet->GetFrame(3));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(4));
    spawnerStand->AddFrame(*enemySheet->GetFrame(5));
    spawnerStand->AddFrame(*enemySheet->GetFrame(4));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));
    spawnerStand->AddFrame(*enemySheet->GetFrame(2));

    phackmanDesinfectWalk.reset(new aether::graphics::Animation(PHACKMAN_WALK_DURATION));
    phackmanDesinfectWalk->AddFrame(*characterSheet->GetFrame(12));
    phackmanDesinfectWalk->AddFrame(*characterSheet->GetFrame(13));
    phackmanDesinfectWalk->AddFrame(*characterSheet->GetFrame(14));
    phackmanDesinfectWalk->AddFrame(*characterSheet->GetFrame(13));

    phackmanDesinfectStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    phackmanDesinfectStand->AddFrame(*characterSheet->GetFrame(13));

    guiFont.Load("assets/bitcell.ttf", 16);
}

Assets::~Assets()
{
    characterBitmap.Destroy();
    enemyBitmap.Destroy();
    maptilesBitmap.Destroy();
    buildingsBitmap.Destroy();
    guiFont.Destroy();
}

void Assets::Initialize()
{
    Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}


