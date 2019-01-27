#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;

Assets::Assets()
{
    characterBitmap.load("assets/phakman-sheet.png");
    characterSheet.reset(new aether::graphics::Spritesheet(3, 5, characterBitmap));

    maptilesBitmap.load("assets/maptiles.png");
    maptilesSheet.reset(new aether::graphics::Spritesheet(6, 15, maptilesBitmap));

    enemyBitmap.load("assets/enemysheet.png");
    enemySheet.reset(new aether::graphics::Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap.load("assets/turrets.png");
    buildingsSheet.reset(new aether::graphics::Spritesheet(4, 2, buildingsBitmap));

    phackmanWalk.reset(new aether::graphics::Animation(0.1e6));
	phackmanWalk->addFrame(characterSheet->getFrame(0));
	phackmanWalk->addFrame(characterSheet->getFrame(1));
	phackmanWalk->addFrame(characterSheet->getFrame(2));
	phackmanWalk->addFrame(characterSheet->getFrame(3));

    phackmanStand.reset(new aether::graphics::Animation(10e6));
    phackmanStand->addFrame(characterSheet->getFrame(1));

    industryNode.reset(new aether::graphics::Animation(10e6));
    industryNode->addFrame(maptilesSheet->getFrame(30));

    powerNode.reset(new aether::graphics::Animation(10e6));
    powerNode->addFrame(maptilesSheet->getFrame(31));

    lsBullet.reset(new aether::graphics::Animation(10e6));
    lsBullet->addFrame(characterSheet->getFrame(11));

    turretStand.reset(new aether::graphics::Animation(10e6));
    turretStand->addFrame(buildingsSheet->getFrame(0));

    turretBullet.reset(new aether::graphics::Animation(10e6));
    turretBullet->addFrame(buildingsSheet->getFrame(1));

    phackmanAttack.reset(new aether::graphics::Animation(7e6));
    phackmanAttack->addFrame(characterSheet->getFrame(8));
	phackmanAttack->addFrame(characterSheet->getFrame(9));

    slimeWalk.reset(new aether::graphics::Animation(1e6));
    slimeWalk->addFrame(characterSheet->getFrame(10));

    spawnerStand.reset(new aether::graphics::Animation(5e5));
    spawnerStand->addFrame(enemySheet->getFrame(0));
    spawnerStand->addFrame(enemySheet->getFrame(0));
    spawnerStand->addFrame(enemySheet->getFrame(0));
    spawnerStand->addFrame(enemySheet->getFrame(0));
    spawnerStand->addFrame(enemySheet->getFrame(1));
    spawnerStand->addFrame(enemySheet->getFrame(1));
    spawnerStand->addFrame(enemySheet->getFrame(1));
    spawnerStand->addFrame(enemySheet->getFrame(1));
    spawnerStand->addFrame(enemySheet->getFrame(3));
    spawnerStand->addFrame(enemySheet->getFrame(3));
    spawnerStand->addFrame(enemySheet->getFrame(3));
    spawnerStand->addFrame(enemySheet->getFrame(3));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(4));
    spawnerStand->addFrame(enemySheet->getFrame(5));
    spawnerStand->addFrame(enemySheet->getFrame(4));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));
    spawnerStand->addFrame(enemySheet->getFrame(2));

    phackmanDesinfectWalk.reset(new aether::graphics::Animation(2e5));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(12));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(13));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(14));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(13));

    phackmanDesinfectStand.reset(new aether::graphics::Animation(1e5));
    phackmanDesinfectStand->addFrame(characterSheet->getFrame(13));

    guiFont = al_load_ttf_font("assets/bitcell.ttf", 16, 0);
}

Assets::~Assets()
{
    characterBitmap.destroy();
    enemyBitmap.destroy();
    maptilesBitmap.destroy();
    buildingsBitmap.destroy();
    al_destroy_font(guiFont);
}

void Assets::Initialize()
{
    Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}


