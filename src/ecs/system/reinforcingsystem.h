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
        x = tlc.current.GetX();
        y = tlc.current.GetY();
        bool is_infected = m_mapScene.IsInfected(x, y);
        bool is_reinforced = m_mapScene.IsReinforced(x, y);
        auto& tc = GetComponent<TransformComponent>(e);
        if( false == is_reinforced && false == is_infected )
        {
            if( rsc.reinforceCells > 0 )
            {
                m_mapScene.Reinforce(tlc.current.GetX(), tlc.current.GetY());
                rsc.reinforceCells--;
                m_factory.MakeCountdownText(tc.position.GetX(), tc.position.GetY(), "powered", aether::graphics::Color::Cyan);
            }
            else
            {
                m_factory.MakeCountdownText(tc.position.GetX(), tc.position.GetY(), "no power cells", aether::graphics::Color::Red);
            }
        }
        else if( true == is_reinforced )
        {
            m_mapScene.UndoReinforce(x, y);
            rsc.reinforceCells++;
            m_factory.MakeCountdownText(tc.position.GetX(), tc.position.GetY(), "unpowered", aether::graphics::Color::Red);
        }
        GetEntityProcessor()->RemoveComponent<ReinforceComponent>(e);
    }

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};
