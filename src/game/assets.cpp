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

    maptilesBitmap.Load("assets/maptiles.png");
    maptilesSheet.reset(new aether::graphics::Spritesheet(6, 15, maptilesBitmap));

    enemyBitmap.Load("assets/enemysheet.png");
    enemySheet.reset(new aether::graphics::Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap.Load("assets/turrets.png");
    buildingsSheet.reset(new aether::graphics::Spritesheet(4, 2, buildingsBitmap));

    // ANIMATIONS
    auto phackmanAnimData = assetsManager.GetAsset<aether::graphics::AsepriteAnimationData>("assets/anim-phackman.json");
    phackmanWalk = phackmanAnimData->anims["PhackWalk"];
    phackmanStand = phackmanAnimData->anims["PhackStand"];
    phackmanAttack = phackmanAnimData->anims["PhackShoot"];
    phackmanDesinfectWalk = phackmanAnimData->anims["PhackWalkInfect"];
    phackmanDesinfectStand = phackmanAnimData->anims["PhackStandInfect"];

    slimeWalk = phackmanAnimData->anims["SlimeWalk"];
	lsBullet = phackmanAnimData->anims["PhackBullet"];
    
    industryNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    industryNode->AddFrame(*maptilesSheet->GetFrame(72));

    powerNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    powerNode->AddFrame(*maptilesSheet->GetFrame(73));

    turretStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretStand->AddFrame(*buildingsSheet->GetFrame(0));

    turretBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretBullet->AddFrame(*buildingsSheet->GetFrame(1));

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

    guiFont = assetsManager.GetAsset<aether::graphics::Font>("assets/bitcell_big.font");
}

Assets::~Assets()
{
    enemyBitmap.Destroy();
    maptilesBitmap.Destroy();
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


