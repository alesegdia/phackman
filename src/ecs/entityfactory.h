#pragma once

#include <secs/secs.h>
#include "components.h"
#include "../game/assets.h"

class EntityFactory
{
public:

    EntityFactory( secs::Engine& world );

    secs::Entity makePlayer( float x, float y );

    secs::Entity makeEnemy( float x, float y );

    secs::Entity makeSpawner( float x, float y );

    secs::Entity makeIndustryNode( float x, float y );

    secs::Entity makePowerNode( float x, float y );

    secs::Entity makeLSBullet( float x, float y, Facing direction );

    secs::Entity makeTurretBullet( float x, float y, Facing direction );

    secs::Entity makeBuildingOnWall( int tile_x, int tile_y, int building_type, Facing facing );

    secs::Entity makeBuildingTurret( const secs::Entity& e );

private:

    secs::Entity makeBullet(float x, float y, Animation::SharedPtr anim , Facing direction, float speed);


	template <typename ComponentType>
	ComponentType& addComponent( const secs::Entity& e )
	{
		return m_world.processor().addComponent<ComponentType>(e);
	}

	secs::Engine& m_world;

};
