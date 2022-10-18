#pragma once

#include <secs/secs.h>
#include "../components.h"
#include "../../map/mapscene.h"

class WallAwarePlacementSystem : public secs::EntitySystem
{
public:
    WallAwarePlacementSystem(MapScene& map_scene)
        : m_mapScene(map_scene)
    {
        SetStepConfiguration(false, false);
        SetNeededComponents<WallAwarePlacedComponent, TileComponent, RenderFacingComponent>();
    }

    void OnEntityAdded(const secs::Entity& e) override
    {
        auto& tlc = GetComponent<TileComponent>(e);
        auto& rfc = GetComponent<RenderFacingComponent>(e);
        m_mapScene.placementMap().setUsedValue(tlc.current.GetX(), tlc.current.GetY(), rfc.facing, true);
    }

    void OnEntityRemoved(const secs::Entity& e) override
    {
        auto& tlc = GetComponent<TileComponent>(e);
        auto& rfc = GetComponent<RenderFacingComponent>(e);
        m_mapScene.placementMap().setUsedValue(tlc.current.GetX(), tlc.current.GetY(), rfc.facing, false);
    }

private:
    MapScene& m_mapScene;

};	

