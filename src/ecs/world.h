#pragma once

#include <secs/secs.h>
#include "component/components.h"

class GameWorld
{
public:

	void makePlayer( float x, float y )
	{
		secs::Entity player = m_world.processor().addEntity();
		auto& transform_comp = addComponent<TransformComponent>(player);
		auto& render_comp = addComponent<RenderComponent>(player);
		auto& animation_comp = addComponent<AnimationComponent>(player);
		auto& facing_comp = addComponent<FacingComponent>(player);
	}

	template <typename ComponentType>
	ComponentType& addComponent( const secs::Entity& e )
	{
		return m_world.processor().addComponent<ComponentType>(e);
	}

private:
	secs::Engine m_world;

};
