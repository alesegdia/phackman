#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;

Assets::Assets()
{
	characterBitmap = al_load_bitmap("assets/phakman-sheet.png");
	characterSheet.reset(new Spritesheet(3, 4, characterBitmap));
	characterAnim.reset(new Animation(0.1f, 3));
	characterAnim->addFrame(characterSheet->getFrame(0));
	characterAnim->addFrame(characterSheet->getFrame(1));
	characterAnim->addFrame(characterSheet->getFrame(2));
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
