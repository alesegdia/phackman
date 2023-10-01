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
        this->SetStepConfiguration(true, true);
        this->SetNeededComponents<InfectComponent, TileComponent>();
    }

    void Process( double delta, const secs::Entity &e ) override
    {
        auto& infect = GetComponent<InfectComponent>(e);

        auto& tlc = GetComponent<TileComponent>(e);
        SECS_UNUSED(e);
        int x, y;
        x = tlc.current.GetX();
        y = tlc.current.GetY();

        if( false == m_mapScene.IsReinforced(x, y) )
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
                    x = tlc.current.GetX();
                    y = tlc.current.GetY();
                    auto& tc = GetComponent<TransformComponent>(e);
                    if( true == infect.desinfect )
                    {
                        bool prev = m_mapScene.IsInfected( x, y );
                        m_mapScene.Desinfect( x, y );
                        if( prev )
                        {
                            m_factory.MakeCountdownText(tc.position.GetX(), tc.position.GetY(), "desinfected");
                        }
                    }
                    else
                    {
                        m_mapScene.Infect( x, y );
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

    void Render( const secs::Entity& e ) override
    {
        auto& infect = GetComponent<InfectComponent>(e);
        auto& tlc = GetComponent<TileComponent>(e);
        int x, y;
        x = tlc.current.GetX();
        y = tlc.current.GetY();

        if( false == m_mapScene.IsReinforced(x, y) )
        {
            bool must_show =
                    ( infect.desinfect &&  m_mapScene.IsInfected(x, y))
                 || (!infect.desinfect && !m_mapScene.IsInfected(x, y));

            if( infect.desinfectTimer > 0 && must_show)
            {
                static constexpr float BORDER   = 4;
                static constexpr float BARSIZE  = 32 - BORDER * 2;
                static constexpr float BARHEIGHT = 3;
                auto tp = aether::math::Vec2i(x * 32, y * 32);
                float xx = infect.desinfectTimer * BARSIZE / infect.desinfectDuration;
                float x0, y0, x1, y1;
                x0 = tp.GetX() + BORDER;
                y0 = tp.GetY() + BORDER;
                x1 = x0 + xx;
                y1 = y0 + BARHEIGHT;
                aether::graphics::draw_filled_rectangle(x0, y0, x1, y1, aether::graphics::Color::Red);
            }
        }
    }

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};
