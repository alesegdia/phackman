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
        setStepConfiguration(false, false);
        setNeededComponents<WallAwarePlacedComponent, TileComponent, RenderFacingComponent>();
    }

    void onAdded(const secs::Entity& e) override
    {
        auto& tlc = component<TileComponent>(e);
        auto& rfc = component<RenderFacingComponent>(e);
        m_mapScene.placementMap().setUsedValue(tlc.current.x(), tlc.current.y(), rfc.facing, true);
    }

    void onRemoved(const secs::Entity& e) override
    {
        auto& tlc = component<TileComponent>(e);
        auto& rfc = component<RenderFacingComponent>(e);
        m_mapScene.placementMap().setUsedValue(tlc.current.x(), tlc.current.y(), rfc.facing, false);
    }

private:
    MapScene& m_mapScene;

};	

