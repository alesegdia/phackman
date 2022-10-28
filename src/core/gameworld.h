#pragma once

#include "../ecs/world.h"
#include "../map/mapscene.h"

class GameWorld
{
public:
    GameWorld();

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

private:
    MapScene m_mapScene;
    ECSWorld m_ecsWorld;
    aether::math::Vec2i m_realMapSize;
    secs::Entity m_playerEntity;
    bool m_gameOver = false;
    std::mt19937 rng;

};
