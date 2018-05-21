#include "world.h"

GameWorld::GameWorld()
	: m_renderingSystem(m_world),
	  m_animationSystem(m_world),
	  m_facingRenderingSystem(m_world),
	  m_keyboardInputSystem(m_world),
	  m_navigationSystem(m_world),
	  m_animatorSystem(m_world),
	  m_factory(m_world)
{
	m_world.pushSystem(&m_renderingSystem);
	m_world.pushSystem(&m_facingRenderingSystem);
	m_world.pushSystem(&m_animationSystem);
	m_world.pushSystem(&m_keyboardInputSystem);
	m_world.pushSystem(&m_navigationSystem);
	m_world.pushSystem(&m_animatorSystem);
}

void GameWorld::step(double delta)
{
	m_world.step( delta );
}

void GameWorld::render()
{
	m_world.render();
}

EntityFactory& GameWorld::factory()
{
	return m_factory;
}

secs::Engine &GameWorld::engine()
{
    return m_world;
}
