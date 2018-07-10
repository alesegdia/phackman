#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../components.h"
#include "../../map/mapscene.h"
#include "../entityfactory.h"

class InfectionSystem : public secs::EntitySystem
{
public:

    InfectionSystem( MapScene& map_scene, EntityFactory& factory )
        : m_mapScene(map_scene),
          m_factory(factory)
    {
        this->setStepConfiguration(true, true);
        this->setNeededComponents<InfectComponent, TileComponent>();
    }

    void process( double delta, const secs::Entity &e ) override
    {
        auto& infect = component<InfectComponent>(e);
        auto& tlc = component<TileComponent>(e);
        SECS_UNUSED(e);
        int x, y;
        x = tlc.current.x();
        y = tlc.current.y();

        if( false == m_mapScene.isReinforced(x, y) )
        {
            if( tlc.previous == tlc.current )
            {
                if( infect.desinfectTimer > 0 )
                {
                    infect.desinfectTimer -= delta;
                }
                else
                {
                    int x, y;
                    x = tlc.current.x();
                    y = tlc.current.y();
                    auto& tc = component<TransformComponent>(e);
                    if( true == infect.desinfect )
                    {
                        bool prev = m_mapScene.isInfected( x, y );
                        m_mapScene.desinfect( x, y );
                        if( prev )
                        {
                            m_factory.makeCountdownText(tc.position.x(), tc.position.y(), "desinfected");
                        }
                    }
                    else
                    {
                        m_mapScene.infect( x, y );
                    }
                }
            }
            else
            {
                infect.desinfectTimer = infect.desinfectDuration;
            }

            if( infect.desinfectTimer < 0 )
            {
                infect.desinfectTimer = 0;
            }
        }
    }

    void render( const secs::Entity& e ) override
    {
        auto& infect = component<InfectComponent>(e);
        auto& tlc = component<TileComponent>(e);
        int x, y;
        x = tlc.current.x();
        y = tlc.current.y();

        if( false == m_mapScene.isReinforced(x, y) )
        {
            bool must_show =
                    ( infect.desinfect &&  m_mapScene.isInfected(x, y))
                 || (!infect.desinfect && !m_mapScene.isInfected(x, y));

            if( infect.desinfectTimer > 0 && must_show)
            {
                auto tp = Vec2i(x * 32, y * 32);
                float xx = infect.desinfectTimer * 16 / infect.desinfectDuration;
                al_draw_filled_rectangle(tp.x() + 2, tp.y() + 2, tp.x() + xx + 2, tp.y() + 2 + 2, al_map_rgb(0, 255, 0));
            }
        }
    }

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};
