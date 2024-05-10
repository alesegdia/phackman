
#pragma once
/*

#include <secs/secs.h>
#include "../components.h"
#include "map/mapscene.h"
#include "ecs/entityfactory.h"

class BombSystem : public secs::TypedEntitySystem<BombComponent, TileComponent>
{
public:
	BombSystem(MapScene& map_scene, EntityFactory& factory)
		: m_mapScene(map_scene),
		  m_factory(factory)
	{

	}

	void CreateBombExplosionDamage(TileComponent& tc, int dx, int dy, int q)
	{
		int x = tc.current.GetX() + dx;
		int y = tc.current.GetY() + dy;
		if (m_mapScene.GetSolidness(x, y) == 0)
		{
			m_factory.MakeBombDamageAreaAtTile(x, y);
			if (q - 1 > 0)
			{
				CreateBombExplosionDamage(tc, dx, dy, q - 1);
			}
		}
	}

	void process( double delta, const secs::Entity& e, BombComponent& bombcomponent, TileComponent& tc )
	{
		bombcomponent.timeToLive -= delta;
		if (bombcomponent.explodedByContact || bombcomponent.timeToLive <= 0)
		{
			m_factory.MakeBombDamageAreaAtTile(tc.current.GetX(), tc.current.GetY());
			CreateBombExplosionDamage(tc,  1,  0, bombcomponent.numLives);
			CreateBombExplosionDamage(tc, -1,  0, bombcomponent.numLives);
			CreateBombExplosionDamage(tc,  0,  1, bombcomponent.numLives);
			CreateBombExplosionDamage(tc,  0, -1, bombcomponent.numLives);
		}
	}

private:
	MapScene& m_mapScene;
	EntityFactory& m_factory;

};	

*/