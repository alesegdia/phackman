#pragma once

#include <secs/secs.h>
#include <aether/aether.h>
#include "components.h"
#include "../game/assets.h"
#include <algorithm>


class EntityFactory
{
public:

    EntityFactory( secs::Engine& world );

    secs::Entity makePlayer(float x, float y, OnDeathActionComponent::Action action);

    secs::Entity makeEnemy( float x, float y, int level );

    secs::Entity makeSpawner( float x, float y );

    secs::Entity makeIndustryNode( float x, float y );

    secs::Entity makePowerNode( float x, float y );

    secs::Entity makeLSBullet( float x, float y, Facing direction );

    secs::Entity MakeTurretBullet( float x, float y, Facing direction );

    secs::Entity MakeBuildingOnWall( int tile_x, int tile_y, int building_type, Facing facing );

    secs::Entity MakeBuildingTurret( const secs::Entity& e );

    secs::Entity MakeCountdownText( float x, float y, const char* text, aether::graphics::Color c = aether::graphics::Color::White);

    secs::Entity MakeCrucible( float x, float y );

    secs::Entity MakeDoor(float x, float y);

    secs::Entity MakeExplosion(float x, float y);

    secs::Entity MakeBombAtTile(float x, float y)
    {

    }

    secs::Entity MakeBombDamageAreaAtTile(float x, float y)
    {

    }


    void MakeExplosions(float x, float y);

private:

    secs::Entity makeBullet(float x, float y, aether::graphics::Animation::SharedPtr anim , Facing direction, float speed);


	template <typename ComponentType>
	ComponentType& AddComponent( const secs::Entity& e )
	{
		return m_world.GetEntityProcessor().AddComponent<ComponentType>(e);
	}

	secs::Engine& m_world;
    secs::Entity m_playerEntity;

};
