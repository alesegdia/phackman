#pragma once

#include <secs/secs.h>
#include "component/components.h"
#include "system/systems.h"

class GameWorld
{
public:

	GameWorld()
		: m_renderingSystem(m_world),
		  m_animationSystem(m_world),
		  m_facingRenderingSystem(m_world)
	{
		m_world.pushSystem(&m_renderingSystem);
		m_world.pushSystem(&m_facingRenderingSystem);
		m_world.pushSystem(&m_animationSystem);
	}

	void makePlayer( float x, float y )
	{
		secs::Entity player = m_world.processor().addEntity();

		auto& transform_comp = addComponent<TransformComponent>(player);
		transform_comp.position.set( x, y );

		auto& render_comp = addComponent<RenderComponent>(player);

		auto& animation_comp = addComponent<AnimationComponent>(player);
		auto& facing_comp = addComponent<FacingComponent>(player);
	}

	template <typename ComponentType>
	ComponentType& addComponent( const secs::Entity& e )
	{
		return m_world.processor().addComponent<ComponentType>(e);
	}

	void step( float delta )
	{
		m_world.step( delta );
	}

	void render()
	{
		m_world.render();
	}

private:
	secs::Engine m_world;
	RenderingSystem m_renderingSystem;
	AnimationSystem m_animationSystem;
	FacingRenderingSystem m_facingRenderingSystem;

};
