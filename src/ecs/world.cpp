#include "world.h"

#include "../ecs/system/systemgroups.h"

GameWorld::GameWorld(MapScene& map_scene)
    : m_factory(m_world),
      m_navigationSystem(map_scene),
      m_infectionSystem(map_scene, m_factory),
      m_wallPlacementSystem(m_world, map_scene, m_factory),
      m_mapAwarenessSystem(map_scene.enemyVisibilityMap()),
      m_placeEnemyInMapSystem(map_scene.enemyVisibilityMap()),
      m_reinforcingSystem(map_scene, m_factory),
      m_poweringSystem(map_scene, m_factory),
      m_playerInputSystem(map_scene, m_factory),
      m_wallAwarePlacementSystem(map_scene)
{
	m_world.pushSystem(&m_renderingSystem);
	m_world.pushSystem(&m_facingRenderingSystem);
	m_world.pushSystem(&m_animationSystem);
    m_world.pushSystem(&m_playerInputSystem);
	m_world.pushSystem(&m_navigationSystem);
	m_world.pushSystem(&m_animatorSystem);
    m_world.pushSystem(&m_wanderSystem);
    m_world.pushSystem(&m_infectionSystem);
    m_world.pushSystem(&m_triggerSystem);
    m_world.pushSystem(&m_shootingSystem);
    m_world.pushSystem(&m_dieOnStopSystem);
    m_world.pushSystem(&m_wallPlacementSystem);
    m_world.pushSystem(&m_computeTileSystem);
    m_world.pushSystem(&m_placeEnemyInMapSystem);
    m_world.pushSystem(&m_mapAwarenessSystem);
    m_world.pushSystem(&m_shootAtSightSystem);
    m_world.pushSystem(&m_hadronCollisionSystem);
    m_world.pushSystem(&m_dieSystem);
    m_world.pushSystem(&m_healthSystem);
    m_world.pushSystem(&m_reinforcingSystem);
    m_world.pushSystem(&m_poweringSystem);
    m_world.pushSystem(&m_disableShootWhenUnpoweredSystem);
    m_world.pushSystem(&m_unpoweredGraphicOverridingSystem);
    m_world.pushSystem(&m_textRenderingSystem);
    m_world.pushSystem(&m_deathCountdownSystem);
    m_world.pushSystem(&m_floatingSystem);
    m_world.pushSystem(&m_fadingSystem);
    m_world.pushSystem(&m_wallAwarePlacementSystem);
    m_world.pushSystem(&m_alwaysShootSystem);

    m_world.activateSystemGroup(SystemGroups::GuiStop);
    m_world.setSystemGroup(&m_playerInputSystem, SystemGroups::GuiStop);
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
