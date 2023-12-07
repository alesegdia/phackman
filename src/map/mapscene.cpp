#include "mapscene.h"

#include "aether/scene/tilemapscenenode.h"

#include "allegro5/allegro_primitives.h"

MapScene::MapScene(int level, std::shared_ptr<aether::scene::Scene> scene)
{
	bool blocked = true;
	while(blocked)
	{
		GenerateMap(level);
		for (auto n1 : m_navmap->GetNodes())
		{
			for (auto n2 : m_navmap->GetNodes())
			{
				std::shared_ptr<PhackmanMapModel> model = std::make_shared<PhackmanMapModel>(m_navmap);
				AStar<PhackmanMapModel> astar(model);
				std::shared_ptr<PhackmanMapModel::Node> nn1 = std::make_shared<PhackmanMapModel::Node>(n1);
				std::shared_ptr<PhackmanMapModel::Node> nn2 = std::make_shared<PhackmanMapModel::Node>(n2);
				nn1->G(0);
				nn1->H(model->hCost(nn1, nn2));
				nn1->computeF();

				astar.restartSearch(nn1, nn2);
				auto retvalue = astar.step();
				while (retvalue == AStarSearchStatus::Running)
				{
					retvalue = astar.step();
				}
				blocked = retvalue == AStarSearchStatus::Blocked;
				if(blocked == true) break;
			}
			if(blocked == true) break;
		}

		if(blocked)
		{
			// m_solidnessMap->DebugPrint();
		}
	}
	m_scene = scene;
	m_renderMapCopy = std::make_shared<aether::math::Matrix2Di>(*m_renderMap);
	m_scene->AddToScene<aether::scene::TilemapSceneNode>(m_renderMapCopy, Assets::instance->maptilesSheet, 16);
}

void MapScene::GenerateMap(int level)
{
	m_map = LayoutBuilder().generate(ShapeStorage().makeSample());
	m_infectionMap = scale_down(*m_map, 2);

	m_solidnessMap = scale_down(*m_map, 2);

	m_placementMap.reset(m_solidnessMap->GetColsNumberInt(), m_solidnessMap->GetRowsNumberInt());

	m_enemyVisibilityMap = scale_down(*m_map, 2);

	m_nodesMap = scale_down(*m_map, 2);
	m_nodesMap = convolute3x3(*m_nodesMap, place_collectible_nodes);
	m_renderMap = convolute3x3(*m_map, draw_map_tiles_convolutor);
	m_renderMap = fill_borders(*m_renderMap, 89);

	m_navmap.reset(new NavigationMap(m_map));

	Blackboard::instance.navigationMap = m_navmap;
}

void MapScene::Infect(int x, int y)
{
	m_infectionMap->SetCell(x, y, 3);
}

void MapScene::Desinfect(int x, int y)
{
	m_infectionMap->SetCell(x, y, 0);
}

void MapScene::UndoReinforce(int x, int y)
{
	Desinfect(x, y);
}

void MapScene::Reinforce(int x, int y)
{
	m_infectionMap->SetCell(x, y, 4);
}

std::shared_ptr<NavigationMap> MapScene::GetNavigationMap()
{
	return m_navmap;
}

aether::math::Matrix2Di::SharedPtr MapScene::GetNodesMap()
{
	return m_nodesMap;
}

aether::math::Matrix2Di::SharedPtr MapScene::GetEnemyVisibilityMap()
{
	return m_enemyVisibilityMap;
}

void MapScene::Render()
{
	for (int r = 0; r < m_renderMap->GetRowsNumberInt(); r++)
	{
		for (int c = 0; c < m_renderMap->GetColsNumberInt(); c++)
		{
			int frame = m_renderMap->GetCell(c, r);

			int ncx, ncy;
			ncx = c / 2;
			ncy = r / 2;

			if (IsInfected(ncx, ncy))
			{
				frame += 24;
			}

			if (IsReinforced(ncx, ncy))
			{
				frame += 48;
			}

			m_renderMapCopy->SetCell(c, r, frame);

		}
	}
}

int MapScene::GetSolidness(int x, int y)
{
	return m_solidnessMap->GetCell(x, y);
}

bool MapScene::IsInfected(int x, int y)
{
	return m_infectionMap->GetCell(x, y) == 3;
}

bool MapScene::IsReinforced(int x, int y)
{
	return m_infectionMap->GetCell(x, y) == 4;
}

void MapScene::ToggleReinforced(int x, int y)
{
	if (false == IsInfected(x, y))
	{
		if (IsReinforced(x, y))
		{
			Desinfect(x, y);
		}
		else
		{
			Reinforce(x, y);
		}
	}
	if (IsReinforced(x, y) && !IsInfected(x, y))
	{

	}
}

aether::math::Vec2f MapScene::GetRenderMapSize()
{
	return aether::math::Vec2f(m_renderMap->GetColsNumberInt(), m_renderMap->GetRowsNumberInt());
}

void MapScene::GetDebugRender()
{
	for (int r = 0; r < m_map->GetRowsNumberInt(); r++)
	{
		for (int c = 0; c < m_map->GetColsNumberInt(); c++)
		{
			int x1, y1, x2, y2;
			x1 = c * 16; y1 = r * 16;
			x2 = (c + 1) * 16; y2 = (r + 1) * 16;

			if (m_map->GetCell(c, r) == 1)
			{
				al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
			}
			else
			{
				al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
			}
		}
	}

	for (PathNode::SharedPtr node : m_navmap->GetNodes())
	{
		float cx, cy;
		cx = (node->x() + 1) * 16;
		cy = (node->y() + 1) * 16;

		for (PathNode::SharedPtr neighboor : node->neighboors())
		{
			int ncx, ncy;
			ncx = (neighboor->x() + 1) * 16;
			ncy = (neighboor->y() + 1) * 16;

			al_draw_line(cx, cy, ncx, ncy, al_map_rgba(0, 255, 255, 2), 1);
		}

		al_draw_filled_circle(cx, cy, 3, al_map_rgb(255, 0, 0));
	}

	for (PathNode::SharedPtr node : m_navmap->GetNodes())
	{
		float x, y;
		x = (node->x() + 1) * 16;
		y = (node->y() + 1) * 16;
		al_draw_ellipse(x, y, 4, 4, al_map_rgb(255, 255, 0), 1);
	}
}

PlacementMap& MapScene::placementMap()
{
	return m_placementMap;
}
