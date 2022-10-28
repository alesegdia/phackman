#pragma once

#include <secs/secs.h>
#include "systems.h"
#include "entityfactory.h"

class ECSWorld
{
public:

    ECSWorld(MapScene &map_scene);

    void step(double delta );

	void Render();

	EntityFactory& factory();

    secs::Engine& engine();

    bool DidPlayerEscape()
    {
	    return m_hadronCollisionSystem->DidPlayerEscape();
    }

private:

    secs::Engine m_world;
    EntityFactory m_factory;

    std::shared_ptr<RenderingSystem>                 m_renderingSystem;
    std::shared_ptr < AnimationSystem>                 m_animationSystem;
    std::shared_ptr < FacingRenderingSystem>           m_facingRenderingSystem;
    std::shared_ptr < MapNavigationSystem   >          m_navigationSystem;
    std::shared_ptr < AnimatorSystem         >         m_animatorSystem;
    std::shared_ptr < AIAgentRandomWanderSystem>       m_wanderSystem;
    std::shared_ptr < InfectionSystem           >      m_infectionSystem;
    std::shared_ptr < TriggerSystem              >     m_triggerSystem;
    std::shared_ptr < ShootingSystem              >    m_shootingSystem;
    std::shared_ptr < DieOnStopSystem              >   m_dieOnStopSystem;
    std::shared_ptr < WallPlacementSystem           >  m_wallPlacementSystem;
    std::shared_ptr < ComputeTileSystem              > m_computeTileSystem;
    std::shared_ptr < MapAwarenessSystem     >         m_mapAwarenessSystem;
    std::shared_ptr < PlaceEnemyInMapSystem   >        m_placeEnemyInMapSystem;
    std::shared_ptr < ShootAtSightSystem       >       m_shootAtSightSystem;
    std::shared_ptr < HadronCollisionSystem     >      m_hadronCollisionSystem;
    std::shared_ptr < DieSystem                  >     m_dieSystem;
    std::shared_ptr < HealthSystem                >    m_healthSystem;
    std::shared_ptr < ReinforcingSystem            >   m_reinforcingSystem;
    std::shared_ptr < PoweringSystem                >  m_poweringSystem;
    std::shared_ptr < DisableShootWhenUnpoweredSystem> m_disableShootWhenUnpoweredSystem;
    std::shared_ptr < UnpoweredGraphicOverridingSystemSystem >m_unpoweredGraphicOverridingSystem;
    std::shared_ptr < PlayerInputSystem            >   m_playerInputSystem;
    std::shared_ptr < TextRenderingSystem           >  m_textRenderingSystem;
    std::shared_ptr < DeathCountdownSystem           > m_deathCountdownSystem;
    std::shared_ptr < FloatingSystem             >     m_floatingSystem;
    std::shared_ptr < FadingSystem                >    m_fadingSystem;
    std::shared_ptr < WallAwarePlacementSystem     >   m_wallAwarePlacementSystem;
    std::shared_ptr < AlwaysShootSystem             >  m_alwaysShootSystem;

};
