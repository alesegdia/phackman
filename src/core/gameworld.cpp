#include "gameworld.h"

GameWorld::GameWorld()
    : m_ecsWorld(m_mapScene)
{
    auto start_node = m_mapScene.navmap()->nodes()[0];

    m_playerEntity = m_ecsWorld.factory().makePlayer(
                (start_node->x()) * 16, (start_node->y()) * 16,
                [&gameOver = this->m_gameOver](auto) {
        gameOver = true;
    });

    m_ecsWorld.factory().makeCrucible((start_node->x()) * 16, (start_node->y()) * 16);

    auto nm = m_mapScene.nodesMap();
    for( int i = 0; i < nm->cols(); i++ )
    {
        for( int j = 0; j < nm->rows(); j++ )
        {
            if( i != 0 && j != 0 && i != nm->cols() -1 && j != nm->rows() - 1)
            {
                auto cell = nm->get(i, j);
                int cx, cy;
                cx = i * 32 + 8;
                cy = j * 32 + 8;
                if( cell == 1 )
                {
                    m_ecsWorld.factory().makeIndustryNode( cx, cy );
                }
                else if (cell == 2 )
                {
                    m_ecsWorld.factory().makePowerNode( cx, cy );
                }
            }
        }
    }

    auto nodes = m_mapScene.navmap()->nodes();
    std::random_shuffle(nodes.begin(), nodes.end());

    for( int i = 0; i < nodes.size() / 10.0f; i++ )
    {
        m_ecsWorld.factory().makeSpawner(nodes[i]->x() * 16, nodes[i]->y() * 16);
    }
}

void GameWorld::step(double delta)
{
    m_ecsWorld.step( delta );
}

void GameWorld::render()
{
    m_mapScene.render();
    m_ecsWorld.render();
}

const Vec2f &GameWorld::playerPos()
{

    return m_ecsWorld.engine().component<TransformComponent>(m_playerEntity).position;
}

const ResourceStorageComponent &GameWorld::playerResourceStorageComponent()
{
    return m_ecsWorld.engine().component<ResourceStorageComponent>(m_playerEntity);
}

bool GameWorld::isGameOver()
{
    return m_gameOver;
}
