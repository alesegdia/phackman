#pragma once

#include <secs/secs.h>
#include "component/components.h"
#include "../game/assets.h"

class EntityFactory
{
public:

	EntityFactory( secs::Engine& world );

	void makePlayer( float x, float y );

	template <typename ComponentType>
	ComponentType& addComponent( const secs::Entity& e )
	{
		return m_world.processor().addComponent<ComponentType>(e);
	}

private:
	secs::Engine& m_world;

};
