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
    characterBitmap.load("assets/phakman-sheet.png");
    characterSheet.reset(new aether::graphics::Spritesheet(3, 5, characterBitmap));

    maptilesBitmap.load("assets/maptiles.png");
    maptilesSheet.reset(new aether::graphics::Spritesheet(6, 15, maptilesBitmap));

    enemyBitmap.load("assets/enemysheet.png");
    enemySheet.reset(new aether::graphics::Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap.load("assets/turrets.png");
    buildingsSheet.reset(new aether::graphics::Spritesheet(4, 2, buildingsBitmap));

    // ANIMATIONS
    phackmanWalk.reset(new aether::graphics::Animation(PHACKMAN_WALK_DURATION));
	phackmanWalk->addFrame(*characterSheet->getFrame(0));
	phackmanWalk->addFrame(*characterSheet->getFrame(1));
	phackmanWalk->addFrame(*characterSheet->getFrame(2));
	phackmanWalk->addFrame(*characterSheet->getFrame(3));

    phackmanStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    phackmanStand->addFrame(*characterSheet->getFrame(1));

    industryNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    industryNode->addFrame(*maptilesSheet->getFrame(30));

    powerNode.reset(new aether::graphics::Animation(STATIC_DURATION));
    powerNode->addFrame(*maptilesSheet->getFrame(31));

    lsBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    lsBullet->addFrame(*characterSheet->getFrame(11));

    turretStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretStand->addFrame(*buildingsSheet->getFrame(0));

    turretBullet.reset(new aether::graphics::Animation(STATIC_DURATION));
    turretBullet->addFrame(*buildingsSheet->getFrame(1));

    phackmanAttack.reset(new aether::graphics::Animation(PHACKMAN_ATTACK_DURATION));
    phackmanAttack->addFrame(*characterSheet->getFrame(9));
    phackmanAttack->addFrame(*characterSheet->getFrame(8));

    slimeWalk.reset(new aether::graphics::Animation(STATIC_DURATION));
    slimeWalk->addFrame(*characterSheet->getFrame(10));

    spawnerStand.reset(new aether::graphics::Animation(0.25e6));
    spawnerStand->addFrame(*enemySheet->getFrame(0));
    spawnerStand->addFrame(*enemySheet->getFrame(0));
    spawnerStand->addFrame(*enemySheet->getFrame(0));
    spawnerStand->addFrame(*enemySheet->getFrame(0));
    spawnerStand->addFrame(*enemySheet->getFrame(1));
    spawnerStand->addFrame(*enemySheet->getFrame(1));
    spawnerStand->addFrame(*enemySheet->getFrame(1));
    spawnerStand->addFrame(*enemySheet->getFrame(1));
    spawnerStand->addFrame(*enemySheet->getFrame(3));
    spawnerStand->addFrame(*enemySheet->getFrame(3));
    spawnerStand->addFrame(*enemySheet->getFrame(3));
    spawnerStand->addFrame(*enemySheet->getFrame(3));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(4));
    spawnerStand->addFrame(*enemySheet->getFrame(5));
    spawnerStand->addFrame(*enemySheet->getFrame(4));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));
    spawnerStand->addFrame(*enemySheet->getFrame(2));

    phackmanDesinfectWalk.reset(new aether::graphics::Animation(PHACKMAN_WALK_DURATION));
    phackmanDesinfectWalk->addFrame(*characterSheet->getFrame(12));
    phackmanDesinfectWalk->addFrame(*characterSheet->getFrame(13));
    phackmanDesinfectWalk->addFrame(*characterSheet->getFrame(14));
    phackmanDesinfectWalk->addFrame(*characterSheet->getFrame(13));

    phackmanDesinfectStand.reset(new aether::graphics::Animation(STATIC_DURATION));
    phackmanDesinfectStand->addFrame(*characterSheet->getFrame(13));

    guiFont.load("assets/bitcell.ttf", 16);
}

Assets::~Assets()
{
    characterBitmap.destroy();
    enemyBitmap.destroy();
    maptilesBitmap.destroy();
    buildingsBitmap.destroy();
    guiFont.destroy();
}

void Assets::Initialize()
{
    Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}


