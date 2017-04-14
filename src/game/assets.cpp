#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;

Assets::Assets()
{
	characterBitmap = al_load_bitmap("assets/phakman-sheet.png");
	characterSheet.reset(new Spritesheet(3, 4, characterBitmap));
    phackmanWalk.reset(new Animation(1.f, 4));
	phackmanWalk->addFrame(characterSheet->getFrame(0));
	phackmanWalk->addFrame(characterSheet->getFrame(1));
	phackmanWalk->addFrame(characterSheet->getFrame(2));
	phackmanWalk->addFrame(characterSheet->getFrame(3));

	maptilesBitmap = al_load_bitmap("assets/maptiles.png");
	maptilesSheet.reset(new Spritesheet(6, 6, maptilesBitmap));
}

Assets::~Assets()
{
	al_destroy_bitmap(characterBitmap);
}

void Assets::Initialize()
{
	Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}


