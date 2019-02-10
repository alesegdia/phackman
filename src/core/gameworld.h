#pragma once

#include "../ecs/world.h"
#include "../map/mapscene.h"

class GameWorld
{
public:
    GameWorld();

    void step(double delta);

    void render();

    const aether::math::Vec2f& playerPos();

    const ResourceStorageComponent& playerResourceStorageComponent();

    bool isGameOver();

    Vec2f mapSize()
    {
        return m_mapScene.renderMapSize();
    }

private:
    MapScene m_mapScene;
    ECSWorld m_ecsWorld;
    Vec2i m_realMapSize;
    secs::Entity m_playerEntity;
    bool m_gameOver = false;

};
