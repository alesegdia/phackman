#include "assets.h"
#include <iostream>

Assets* Assets::instance = nullptr;

Assets::Assets()
{
	characterSheet = al_load_bitmap("assets/phakman-sheet.png");
	std::cout << characterSheet;
}

Assets::~Assets()
{
	al_destroy_bitmap(characterSheet);
}

void Assets::Initialize()
{
	std::cout << "initing";
	Assets::instance = new Assets();
}

void Assets::Dispose()
{
	delete instance;
}
