#include "gameworld.h"
#include <algorithm>

GameWorld::GameWorld()
    : m_ecsWorld(m_mapScene)
{
    rng.seed(time(NULL) + 0xFACEFEED);
    auto start_node = m_mapScene.navmap()->nodes()[0];

    m_playerEntity = m_ecsWorld.factory().makePlayer(
                (start_node->x()) * 16, (start_node->y()) * 16,
                [&gameOver = this->m_gameOver](auto) {
        gameOver = true;
    });

    m_ecsWorld.factory().makeCrucible((start_node->x()) * 16, (start_node->y()) * 16);

    auto nm = m_mapScene.nodesMap();
    for( int i = 0; i < nm->GetColsNumber(); i++ )
    {
        for( int j = 0; j < nm->GetRowsNumber(); j++ )
        {
            if( i != 0 && j != 0 && i != nm->GetColsNumber() -1 && j != nm->GetRowsNumber() - 1)
            {
                auto cell = nm->GetCell(i, j);
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
    std::shuffle(nodes.begin(), nodes.end(), rng);

    for( int i = 0; i < nodes.size() / 10.0f; i++ )
    {
        m_ecsWorld.factory().makeSpawner(nodes[i]->x() * 16, nodes[i]->y() * 16);
    }
}

void GameWorld::step(double delta)
{
    m_ecsWorld.step( delta );
}

void GameWorld::Render()
{
    m_mapScene.Render();
    m_ecsWorld.Render();
}

const aether::math::Vec2f &GameWorld::playerPos()
{

    return m_ecsWorld.engine().GetComponent<TransformComponent>(m_playerEntity).position;
}

const ResourceStorageComponent &GameWorld::playerResourceStorageComponent()
{
    return m_ecsWorld.engine().GetComponent<ResourceStorageComponent>(m_playerEntity);
}

bool GameWorld::isGameOver()
{
    return m_gameOver;
}
