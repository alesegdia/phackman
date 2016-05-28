#pragma once

#include "component/components.h"

#include <secs/secs.h>
#include "system/systems.h"
#include "../game/assets.h"

class GameWorld
{
public:

	GameWorld()
		: m_renderingSystem(m_world),
		  m_animationSystem(m_world),
		  m_facingRenderingSystem(m_world),
		  m_keyboardInputSystem(m_world),
		  m_navigationSystem(m_world)
	{
		m_world.pushSystem(&m_renderingSystem);
		m_world.pushSystem(&m_facingRenderingSystem);
		m_world.pushSystem(&m_animationSystem);
		m_world.pushSystem(&m_keyboardInputSystem);
		m_world.pushSystem(&m_navigationSystem);
	}

	void makePlayer( float x, float y )
	{
		secs::Entity player = m_world.processor().addEntity();

		auto& transform_comp = addComponent<TransformComponent>(player);
		transform_comp.position.set( x, y );

		addComponent<RenderComponent>(player);

		auto& animation_comp = addComponent<AnimationComponent>(player);
		animation_comp.animation = Assets::instance->phackmanWalk;

		addComponent<RenderFacingComponent>(player);
		addComponent<KeyboardInputComponent>(player);

		addComponent<MapAgentInputComponent>(player);
		addComponent<MapAgentStateComponent>(player);
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
	KeyboardInputSystem m_keyboardInputSystem;
	MapNavigationSystem m_navigationSystem;

};
