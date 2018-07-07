#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../components.h"
#include "../../map/mapscene.h"


class InfectionSystem : public secs::TypedEntitySystem<InfectComponent, TileComponent>
{
public:

    InfectionSystem( secs::Engine& world, MapScene& map_scene )
        : m_world(world),
          m_mapScene(map_scene)
    {
        this->setStepConfiguration(true, true);
    }

    void process( double delta, const secs::Entity &e, InfectComponent& infect, TileComponent& tlc ) override
    {
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
                    if( true == infect.desinfect )
                    {
                        m_mapScene.desinfect( x, y );
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
        auto& infect = m_world.component<InfectComponent>(e);
        auto& tlc = m_world.component<TileComponent>(e);
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
    secs::Engine& m_world;
    MapScene& m_mapScene;

};
