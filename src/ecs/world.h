#pragma once

#include <secs/secs.h>
#include "system/systems.h"
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
	RenderingSystem m_renderingSystem;
	AnimationSystem m_animationSystem;
	FacingRenderingSystem m_facingRenderingSystem;
	KeyboardInputSystem m_keyboardInputSystem;
	MapNavigationSystem m_navigationSystem;
	AnimatorSystem m_animatorSystem;
    AIAgentRandomWanderSystem m_wanderSystem;
    InfectionSystem m_infectionSystem;
    TriggerSystem m_triggerSystem;
    ShootingSystem m_shootingSystem;
    DieOnStopSystem m_dieOnStopSystem;
    WallPlacementSystem m_wallPlacementSystem;
    ComputeTileSystem m_computeTileSystem;
    PlaceEnemyInMapSystem m_placeEnemyInMapSystem;
    MapAwarenessSystem m_mapAwarenessSystem;
    ShootAtSightSystem m_shootAtSightSystem;
    HadronCollisionSystem m_hadronCollisionSystem;
    EntityFactory m_factory;

};
