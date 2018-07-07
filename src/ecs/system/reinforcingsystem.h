#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../component/components.h"
#include "../../map/mapscene.h"


class ReinforcingSystem : public secs::TypedEntitySystem<ReinforceComponent, TileComponent, ResourceStorageComponent>
{
public:

    ReinforcingSystem( MapScene& map_scene )
        : m_mapScene(map_scene)
    {

    }

    void process( double delta, const secs::Entity &e,
                  ReinforceComponent& rc,
                  TileComponent& tlc,
                  ResourceStorageComponent& rsc ) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(rc);
        int x, y;
        x = tlc.current.x();
        y = tlc.current.y();
        bool is_infected = m_mapScene.isInfected(x, y);
        bool is_reinforced = m_mapScene.isReinforced(x, y);
        if( false == is_reinforced && false == is_infected && rsc.reinforceNodes > 0 )
        {
            m_mapScene.reinforce(tlc.current.x(), tlc.current.y());
            rsc.reinforceNodes--;
        }
        else if( true == is_reinforced )
        {
            m_mapScene.undoReinforce(x, y);
            rsc.reinforceNodes++;
        }
        processor()->removeComponent<ReinforceComponent>(e);
    }

private:
    MapScene& m_mapScene;

};
