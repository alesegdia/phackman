#pragma once

#include "aether/scene/scene.h"

#include "../map/mapgen.h"
#include "../map/placementmap.h"
#include "../ai/pfmap.h"
#include "../ai/blackboard.h"
#include "../game/assets.h"
#include "secs/entity.h"

class MapScene
{
public:
    MapScene(int level, std::shared_ptr<aether::scene::Scene> scene);

    void GenerateMap(int level);

    void Infect(int x, int y);

    void Desinfect(int x, int y);

    void UndoReinforce(int x, int y);

    void Reinforce(int x, int y);

    std::shared_ptr<NavigationMap> GetNavigationMap();

    aether::math::Matrix2Di::SharedPtr GetNodesMap();

    aether::math::Matrix2Di::SharedPtr GetEnemyVisibilityMap();

    void Render();

    int GetSolidness(int x, int y);

    bool IsInfected(int x, int y);

    bool IsInfected(const aether::math::Vec2i& v)
    {
        return IsInfected(v.GetX(), v.GetY());
    }

    bool IsReinforced(int x, int y);

    bool IsReinforced(const aether::math::Vec2i& v)
    {
        return IsReinforced(v.GetX(), v.GetY());
    }

    void ToggleReinforced(int x, int y);

    aether::math::Vec2f GetRenderMapSize();

    void GetDebugRender();

    PlacementMap& placementMap();

    void SetCrucibleEntity(secs::Entity e)
    {
        m_crucibleEntity = e;
    }

    secs::Entity GetCrucibleEntity()
    {
        return m_crucibleEntity;
    }

    void SetExitEntity(secs::Entity e)
    {
        m_exitEntity = e;
    }

    secs::Entity GetExitEntity()
    {
	    return m_exitEntity;
    }


private:
    aether::math::Matrix2Di::SharedPtr m_map;
    aether::math::Matrix2Di::SharedPtr m_renderMap;
    aether::math::Matrix2Di::SharedPtr m_renderMapCopy;
    aether::math::Matrix2Di::SharedPtr m_infectionMap;
    std::shared_ptr<NavigationMap> m_navmap;
    PlacementMap m_placementMap;

    aether::math::Matrix2Di::SharedPtr m_nodesMap;
    aether::math::Matrix2Di::SharedPtr m_solidnessMap;
    aether::math::Matrix2Di::SharedPtr m_enemyVisibilityMap;

    secs::Entity m_crucibleEntity;
    secs::Entity m_exitEntity;

    std::shared_ptr<aether::scene::Scene> m_scene;

};

