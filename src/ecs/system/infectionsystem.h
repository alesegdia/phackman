#pragma once

#include <secs/secs.h>
#include <aether/aether.h>
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
                static constexpr float BORDER   = 4;
                static constexpr float BARSIZE  = 32 - BORDER * 2;
                static constexpr float BARHEIGHT = 3;
                auto tp = aether::math::Vec2i(x * 32, y * 32);
                float xx = infect.desinfectTimer * BARSIZE / infect.desinfectDuration;
                float x0, y0, x1, y1;
                x0 = tp.x() + BORDER;
                y0 = tp.y() + BORDER;
                x1 = x0 + xx;
                y1 = y0 + BARHEIGHT;
                al_draw_filled_rectangle(x0, y0, x1, y1, al_map_rgb(0, 255, 0));
            }
        }
    }

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};
