#pragma once

#include "../ecs/world.h"
#include "../map/mapscene.h"

class GameWorld
{
public:
    GameWorld(std::shared_ptr<aether::scene::Scene> scene);

    void step(double delta);

    void Render();

    const aether::math::Vec2f& playerPos();

    const ResourceStorageComponent& playerResourceStorageComponent();

    bool isGameOver();

    aether::math::Vec2f mapSize()
    {
        return m_mapScene.GetRenderMapSize();
    }

    bool DidPlayerEscape()
    {
	    return m_ecsWorld.DidPlayerEscape();
    }

    bool PlayerHoldsCore()
    {
        const auto& aic = m_ecsWorld.engine().GetEntityProcessor().Component<AgentInputComponent>(m_playerEntity);
        return aic.carryCrucible;
    }

    bool IsPlayerInfected()
    {
        return m_mapScene.IsInfected(GetPlayerTile());
    }

    bool IsPlayerReinforced()
    {
        return m_mapScene.IsReinforced(GetPlayerTile());
    }

    bool PlayerOverCrucible()
    {
        auto crucibleTile = GetCrucibleTile();
        auto playerTile = GetPlayerTile();
        return crucibleTile == playerTile;
    }

    bool PlayerOverExit()
    {
        auto crucibleTile = GetExitTile();
        auto playerTile = GetPlayerTile();
        return crucibleTile == playerTile;
    }

private:

    aether::math::Vec2i GetPlayerTile()
    {
        return m_ecsWorld.engine().GetEntityProcessor().Component<TileComponent>(m_playerEntity).current;
    }
    aether::math::Vec2i GetCrucibleTile()
    {
        return m_ecsWorld.engine().GetEntityProcessor().Component<TileComponent>(m_mapScene.GetCrucibleEntity()).current;
    }

    aether::math::Vec2i GetExitTile()
    {
        return m_ecsWorld.engine().GetEntityProcessor().Component<TileComponent>(m_mapScene.GetExitEntity()).current;
    }


    MapScene m_mapScene;
    ECSWorld m_ecsWorld;
    aether::math::Vec2i m_realMapSize;
    secs::Entity m_playerEntity;
    bool m_gameOver = false;
    std::mt19937 rng;
    std::shared_ptr<aether::scene::Scene> m_scene;

};
