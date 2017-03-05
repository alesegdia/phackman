#pragma once

#include <secs/secs.h>
#include "system/systems.h"
#include "entityfactory.h"

class GameWorld
{
public:

	GameWorld();

	void step( float delta );

	void render();

	EntityFactory& factory();

    secs::Engine& engine();

private:
	secs::Engine m_world;
	RenderingSystem m_renderingSystem;
	AnimationSystem m_animationSystem;
	FacingRenderingSystem m_facingRenderingSystem;
	KeyboardInputSystem m_keyboardInputSystem;
	MapNavigationSystem m_navigationSystem;
	EntityFactory m_factory;

};
