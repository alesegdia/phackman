#pragma once

#include <secs/secs.h>
#include "systems.h"
#include "entityfactory.h"

class GameWorld
{
public:

    GameWorld(MapScene &map_scene);

    void step(double delta );

	void render();

	EntityFactory& factory();

    secs::Engine& engine();

private:

    secs::Engine m_world;
    EntityFactory m_factory;

    RenderingSystem                 m_renderingSystem;
    AnimationSystem                 m_animationSystem;
    FacingRenderingSystem           m_facingRenderingSystem;
    MapNavigationSystem             m_navigationSystem;
    AnimatorSystem                  m_animatorSystem;
    AIAgentRandomWanderSystem       m_wanderSystem;
    InfectionSystem                 m_infectionSystem;
    TriggerSystem                   m_triggerSystem;
    ShootingSystem                  m_shootingSystem;
    DieOnStopSystem                 m_dieOnStopSystem;
    WallPlacementSystem             m_wallPlacementSystem;
    ComputeTileSystem               m_computeTileSystem;
    MapAwarenessSystem              m_mapAwarenessSystem;
    PlaceEnemyInMapSystem           m_placeEnemyInMapSystem;
    ShootAtSightSystem              m_shootAtSightSystem;
    HadronCollisionSystem           m_hadronCollisionSystem;
    DieSystem                       m_dieSystem;
    HealthSystem                    m_healthSystem;
    ReinforcingSystem               m_reinforcingSystem;
    PoweringSystem                  m_poweringSystem;
    DisableShootWhenUnpoweredSystem m_disableShootWhenUnpoweredSystem;
    UnpoweredGraphicOverridingSystemSystem m_unpoweredGraphicOverridingSystem;
    PlayerInputSystem               m_playerInputSystem;
    TextRenderingSystem             m_textRenderingSystem;
    DeathCountdownSystem            m_deathCountdownSystem;
    FloatingSystem                  m_floatingSystem;
    FadingSystem                    m_fadingSystem;

};
