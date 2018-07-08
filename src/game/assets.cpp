#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;

Assets::Assets()
{
	characterBitmap = al_load_bitmap("assets/phakman-sheet.png");
    characterSheet.reset(new Spritesheet(3, 5, characterBitmap));

    maptilesBitmap = al_load_bitmap("assets/maptiles.png");
    maptilesSheet.reset(new Spritesheet(6, 15, maptilesBitmap));

    enemyBitmap = al_load_bitmap("assets/enemysheet.png");
    enemySheet.reset(new Spritesheet(4, 2, enemyBitmap));

    buildingsBitmap = al_load_bitmap("assets/turrets.png");
    buildingsSheet.reset(new Spritesheet(4, 2, buildingsBitmap));

    phackmanWalk.reset(new Animation(1.f, 4));
	phackmanWalk->addFrame(characterSheet->getFrame(0));
	phackmanWalk->addFrame(characterSheet->getFrame(1));
	phackmanWalk->addFrame(characterSheet->getFrame(2));
	phackmanWalk->addFrame(characterSheet->getFrame(3));

    phackmanStand.reset(new Animation(1.f, 1));
    phackmanStand->addFrame(characterSheet->getFrame(1));

    industryNode.reset(new Animation(1.f, 1));
    industryNode->addFrame(maptilesSheet->getFrame(30));

    powerNode.reset(new Animation(1.f, 1));
    powerNode->addFrame(maptilesSheet->getFrame(31));

    lsBullet.reset(new Animation(1.f, 1));
    lsBullet->addFrame(characterSheet->getFrame(11));

    turretStand.reset(new Animation(1.f, 1));
    turretStand->addFrame(buildingsSheet->getFrame(0));

    turretBullet.reset(new Animation(1.f, 1));
    turretBullet->addFrame(buildingsSheet->getFrame(1));

    phackmanAttack.reset(new Animation(.7f, 2));
    phackmanAttack->addFrame(characterSheet->getFrame(8));
	phackmanAttack->addFrame(characterSheet->getFrame(9));

    slimeWalk.reset(new Animation(1.f, 1));
    slimeWalk->addFrame(characterSheet->getFrame(10));

    spawnerStand.reset(new Animation(0.5f, 23));
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

    phackmanDesinfectWalk.reset(new Animation(2.f, 4));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(12));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(13));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(14));
    phackmanDesinfectWalk->addFrame(characterSheet->getFrame(13));

    phackmanDesinfectStand.reset(new Animation(1.f, 1));
    phackmanDesinfectStand->addFrame(characterSheet->getFrame(13));

    guiFont = al_load_ttf_font("assets/bitcell.ttf", 16, 0);
}

Assets::~Assets()
{
	al_destroy_bitmap(characterBitmap);
    al_destroy_bitmap(enemyBitmap);
    al_destroy_bitmap(maptilesBitmap);
    al_destroy_bitmap(buildingsBitmap);
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


