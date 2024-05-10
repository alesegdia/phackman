#include "world.h"

#include "../ecs/system/systemgroups.h"

ECSWorld::ECSWorld(MapScene& map_scene)
    : m_factory(m_world)
{
	m_renderingSystem = m_world.CreateSystem<RenderingSystem>();
    m_facingRenderingSystem = m_world.CreateSystem<FacingRenderingSystem>();
    m_animationSystem = m_world.CreateSystem<AnimationSystem>();
    m_playerInputSystem = m_world.CreateSystem<PlayerInputSystem>(map_scene, m_factory);
    m_navigationSystem = m_world.CreateSystem<MapNavigationSystem>(map_scene);
    m_animatorSystem = m_world.CreateSystem<AnimatorSystem>();
    m_wanderSystem = m_world.CreateSystem<AIAgentRandomWanderSystem>();
    m_infectionSystem = m_world.CreateSystem<InfectionSystem>(map_scene, m_factory);
    m_triggerSystem = m_world.CreateSystem<TriggerSystem>();

    m_shootingSystem = m_world.CreateSystem<ShootingSystem>();
    m_dieOnStopSystem = m_world.CreateSystem<DieOnStopSystem>();
    m_wallPlacementSystem = m_world.CreateSystem<WallPlacementSystem>(m_world, map_scene, m_factory);
    m_computeTileSystem = m_world.CreateSystem<ComputeTileSystem>();
    m_placeEnemyInMapSystem = m_world.CreateSystem<PlaceEnemyInMapSystem>(map_scene.GetEnemyVisibilityMap());
    m_mapAwarenessSystem = m_world.CreateSystem<MapAwarenessSystem>(map_scene.GetEnemyVisibilityMap());
    m_shootAtSightSystem = m_world.CreateSystem<ShootAtSightSystem>();
    m_hadronCollisionSystem = m_world.CreateSystem<HadronCollisionSystem>();
    m_healthSystem = m_world.CreateSystem<HealthSystem>();
    m_reinforcingSystem = m_world.CreateSystem<ReinforcingSystem>(map_scene, m_factory);
    m_poweringSystem = m_world.CreateSystem<PoweringSystem>(map_scene, m_factory);
    m_disableShootWhenUnpoweredSystem = m_world.CreateSystem<DisableShootWhenUnpoweredSystem>();
    m_unpoweredGraphicOverridingSystem = m_world.CreateSystem<UnpoweredGraphicOverridingSystemSystem>();
    m_textRenderingSystem = m_world.CreateSystem<TextRenderingSystem>();
    m_deathCountdownSystem = m_world.CreateSystem<DeathCountdownSystem>();
    m_floatingSystem = m_world.CreateSystem<FloatingSystem>();
    m_fadingSystem = m_world.CreateSystem<FadingSystem>();
    m_wallAwarePlacementSystem = m_world.CreateSystem<WallAwarePlacementSystem>(map_scene);
    m_alwaysShootSystem = m_world.CreateSystem<AlwaysShootSystem>();
    m_dieSystem = m_world.CreateSystem<DieSystem>();
    m_damageSystem = m_world.CreateSystem<DamageSystem>();

    m_world.ActivateSystemGroup(SystemGroups::GuiStop);
    m_world.SetSystemGroup(m_playerInputSystem, SystemGroups::GuiStop);
}

void ECSWorld::step(double delta)
{
	m_world.Step( delta );
}

void ECSWorld::Render()
{
	m_world.Render();
}

EntityFactory& ECSWorld::factory()
{
	return m_factory;
}

secs::Engine &ECSWorld::engine()
{
    return m_world;
}
