#pragma once

#include <secs/secs.h>
#include "../components.h"
#include "../../map/mapscene.h"
#include "../entityfactory.h"


class ReinforcingSystem : public secs::TypedEntitySystem<ReinforceComponent, TileComponent, ResourceStorageComponent>
{
public:

    ReinforcingSystem( MapScene& map_scene, EntityFactory& factory )
        : m_mapScene(map_scene), m_factory(factory)
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
        auto& tc = component<TransformComponent>(e);
        if( false == is_reinforced && false == is_infected )
        {
            if( rsc.reinforceCells > 0 )
            {
                m_mapScene.reinforce(tlc.current.x(), tlc.current.y());
                rsc.reinforceCells--;
                m_factory.makeCountdownText(tc.position.x(), tc.position.y(), "powered");
            }
            else
            {
                m_factory.makeCountdownText(tc.position.x(), tc.position.y(), "no power cells");
            }
        }
        else if( true == is_reinforced )
        {
            m_mapScene.undoReinforce(x, y);
            rsc.reinforceCells++;
            m_factory.makeCountdownText(tc.position.x(), tc.position.y(), "unpowered");
        }
        processor()->removeComponent<ReinforceComponent>(e);
    }

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};
