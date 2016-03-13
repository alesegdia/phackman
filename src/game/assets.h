#pragma once

#include <memory>
#include <allegro5/allegro.h>
#include "../core/spritesheet.h"
#include "../core/animation.h"

class Assets
{
public:

	// singleton interface
	static Assets* instance;
	static void Initialize();
	static void Dispose();

	Assets();
	~Assets();

	ALLEGRO_BITMAP* characterBitmap;
	ALLEGRO_BITMAP* maptilesBitmap;
	std::shared_ptr<Spritesheet> characterSheet;
	std::shared_ptr<Animation> phackmanWalk;
	std::shared_ptr<Spritesheet> maptilesSheet;

};
