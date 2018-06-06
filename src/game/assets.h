#pragma once

#include <memory>
#include <allegro5/allegro.h>

#include <alligator/graphics/spritesheet.h>
#include <alligator/graphics/animation.h>

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
    ALLEGRO_BITMAP* enemyBitmap;
    ALLEGRO_BITMAP* maptilesBitmap;
    ALLEGRO_BITMAP* buildingsBitmap;

    std::shared_ptr<Spritesheet> characterSheet;
    std::shared_ptr<Spritesheet> enemySheet;
    std::shared_ptr<Spritesheet> buildingsSheet;
    std::shared_ptr<Spritesheet> maptilesSheet;

    std::shared_ptr<Animation> industryNode;
    std::shared_ptr<Animation> powerNode;

    std::shared_ptr<Animation> lsBullet;

    std::shared_ptr<Animation> phackmanWalk;
    std::shared_ptr<Animation> phackmanStand;
	std::shared_ptr<Animation> phackmanAttack;

    std::shared_ptr<Animation> phackmanDesinfectStand;
    std::shared_ptr<Animation> phackmanDesinfectWalk;

    std::shared_ptr<Animation> slimeWalk;

    std::shared_ptr<Animation> spawnerStand;
    std::shared_ptr<Animation> turretStand;


};
