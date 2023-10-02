#include "gameworld.h"
#include <algorithm>

GameWorld::GameWorld(std::shared_ptr<aether::scene::Scene> scene)
	: m_mapScene(0, scene),
      m_ecsWorld(m_mapScene),
      m_scene(scene)
{
    rng.seed(time(NULL) + 0xFACEFEED);
    auto start_node = m_mapScene.GetNavigationMap()->GetNodes()[0];

    float max_dist = 0;
    std::shared_ptr<PathNode> doorNode = nullptr;
    auto startNodePos = start_node->GetPosition();
    for(auto node : m_mapScene.GetNavigationMap()->GetNodes())
    {
	    auto currentNodePos = node->GetPosition();
        auto dist = aether::math::Vec2i::EuclideanDistance(startNodePos, currentNodePos);
        if(dist > max_dist)
        {
	        max_dist = dist;
            doorNode = node;
        }
    }

    m_ecsWorld.factory().MakeDoor(doorNode->x() * 16, doorNode->y() * 16);

    m_playerEntity = m_ecsWorld.factory().makePlayer(
                (start_node->x()) * 16, (start_node->y()) * 16,
                [&gameOver = this->m_gameOver](auto) {
        gameOver = true;
    });

    auto crucibleEntity = m_ecsWorld.factory().MakeCrucible((start_node->x()) * 16, (start_node->y()) * 16);
    m_mapScene.SetCrucibleEntity(crucibleEntity);

    auto nm = m_mapScene.GetNodesMap();
    for( int i = 0; i < nm->GetColsNumber(); i++ )
    {
        for( int j = 0; j < nm->GetRowsNumberInt(); j++ )
        {
            if( i != 0 && j != 0 && i != nm->GetColsNumberInt() -1 && j != nm->GetRowsNumberInt() - 1)
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

	std::shared_ptr<PhackmanMapModel> model = std::make_shared<PhackmanMapModel>(m_mapScene.GetNavigationMap());
	AStar<PhackmanMapModel> astar(model);
	std::shared_ptr<PhackmanMapModel::Node> nn1 = std::make_shared<PhackmanMapModel::Node>(start_node);
	std::shared_ptr<PhackmanMapModel::Node> nn2 = std::make_shared<PhackmanMapModel::Node>(doorNode);
	nn1->G(0);
	nn1->H(model->hCost(nn1, nn2));
	nn1->computeF();

	astar.restartSearch(nn1, nn2);
	auto retvalue = astar.step();
	while (retvalue == AStarSearchStatus::Running)
	{
		retvalue = astar.step();
	}
	assert(retvalue == AStarSearchStatus::Finished);
	auto solution = astar.solution();

    auto nodes = m_mapScene.GetNavigationMap()->GetNodes();
    std::shuffle(nodes.begin(), nodes.end(), rng);

    auto numSpawners = 0;
    int i = 0;

    auto spawnersToSpawn = nodes.size() / 7.0f;
    while(numSpawners < spawnersToSpawn)
    {
        if(nodes[i]->GetPosition() != doorNode->GetPosition() &&
			nodes[i]->GetPosition() != start_node->GetPosition())
        {
            bool inMiddleOfSolution = false;
            for(auto soln : solution)
            {
                inMiddleOfSolution = soln->node->GetPosition() == nodes[i]->GetPosition();
                if(inMiddleOfSolution) break;
            }
            if(!inMiddleOfSolution)
            {
				m_ecsWorld.factory().makeSpawner(nodes[i]->x() * 16, nodes[i]->y() * 16);
                numSpawners++;
            }
        }
		i++;
        if(i == nodes.size())
        {
	        break;
        }
    }

}

void GameWorld::step(double delta)
{
    m_ecsWorld.step( delta );
}

void GameWorld::Render()
{
    m_mapScene.Render();
    m_scene->Render();
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
