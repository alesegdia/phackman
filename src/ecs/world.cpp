#include "world.h"

#include "../ecs/system/systemgroups.h"

ECSWorld::ECSWorld(MapScene& map_scene)
    : m_factory(m_world)
{
	m_renderingSystem = m_world.createSystem<RenderingSystem>();
    m_facingRenderingSystem = m_world.createSystem<FacingRenderingSystem>();
    m_animationSystem = m_world.createSystem<AnimationSystem>();
    m_playerInputSystem = m_world.createSystem<PlayerInputSystem>(map_scene, m_factory);
    m_navigationSystem = m_world.createSystem<MapNavigationSystem>(map_scene);
    m_animatorSystem = m_world.createSystem<AnimatorSystem>();
    m_wanderSystem = m_world.createSystem<AIAgentRandomWanderSystem>();
    m_infectionSystem = m_world.createSystem<InfectionSystem>(map_scene, m_factory);
    m_triggerSystem = m_world.createSystem<TriggerSystem>();

    m_shootingSystem = m_world.createSystem<ShootingSystem>();
    m_dieOnStopSystem = m_world.createSystem<DieOnStopSystem>();
    m_wallPlacementSystem = m_world.createSystem<WallPlacementSystem>(m_world, map_scene, m_factory);
    m_computeTileSystem = m_world.createSystem<ComputeTileSystem>();
    m_placeEnemyInMapSystem = m_world.createSystem<PlaceEnemyInMapSystem>(map_scene.enemyVisibilityMap());
    m_mapAwarenessSystem = m_world.createSystem<MapAwarenessSystem>(map_scene.enemyVisibilityMap());
    m_shootAtSightSystem = m_world.createSystem<ShootAtSightSystem>();
    m_hadronCollisionSystem = m_world.createSystem<HadronCollisionSystem>();
    m_dieSystem = m_world.createSystem<DieSystem>();
    m_healthSystem = m_world.createSystem<HealthSystem>();
    m_reinforcingSystem = m_world.createSystem<ReinforcingSystem>(map_scene, m_factory);
    m_poweringSystem = m_world.createSystem<PoweringSystem>(map_scene, m_factory);
    m_disableShootWhenUnpoweredSystem = m_world.createSystem<DisableShootWhenUnpoweredSystem>();
    m_unpoweredGraphicOverridingSystem = m_world.createSystem<UnpoweredGraphicOverridingSystemSystem>();
    m_textRenderingSystem = m_world.createSystem<TextRenderingSystem>();
    m_deathCountdownSystem = m_world.createSystem<DeathCountdownSystem>();
    m_floatingSystem = m_world.createSystem<FloatingSystem>();
    m_fadingSystem = m_world.createSystem<FadingSystem>();
    m_wallAwarePlacementSystem = m_world.createSystem<WallAwarePlacementSystem>(map_scene);
    m_alwaysShootSystem = m_world.createSystem<AlwaysShootSystem>();

    m_world.activateSystemGroup(SystemGroups::GuiStop);
    m_world.setSystemGroup(m_playerInputSystem, SystemGroups::GuiStop);
}

void ECSWorld::step(double delta)
{
	m_world.step( delta );
}

void ECSWorld::render()
{
	m_world.render();
}

EntityFactory& ECSWorld::factory()
{
	return m_factory;
}

secs::Engine &ECSWorld::engine()
{
    return m_world;
}
