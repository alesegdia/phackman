#pragma once

#include <secs/secs.h>
#include "system/systems.h"
#include "entityfactory.h"

class GameWorld
{
public:

	GameWorld();

    void step(double delta );

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
	AnimatorSystem m_animatorSystem;
	EntityFactory m_factory;

};
