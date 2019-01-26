#pragma once

#include "../ecs/world.h"

class GameWorld
{
public:
    GameWorld();

    void step(double delta);

    void render();

    const Vec2f& playerPos();

    const ResourceStorageComponent& playerResourceStorageComponent();

    bool isGameOver();

private:
    MapScene m_mapScene;
    ECSWorld m_ecsWorld;
    secs::Entity m_playerEntity;
    bool m_gameOver = false;

};
