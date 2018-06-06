#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../component/components.h"
#include "../../map/mapscene.h"


class InfectionSystem : public secs::EntitySystem
{
public:

    InfectionSystem( secs::Engine& world, MapScene& map_scene )
        : m_world(world),
          m_mapScene(map_scene)
    {
        this->setStepConfiguration(true, true);
        setNeededComponents<InfectComponent,
                            TransformComponent>();
    }

    void process( double delta, const secs::Entity &e ) override
    {

        auto& transform = m_world.component<TransformComponent>(e);
        auto& infect = m_world.component<InfectComponent>(e);

        int x = (transform.position.x()+16) / 32;
        int y = (transform.position.y()+16) / 32;


        if( infect.last_x == x && infect.last_y == y )
        {
            if( infect.desinfectTimer > 0 )
            {
                infect.desinfectTimer -= delta;
            }
            else
            {
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
        infect.last_x = x;
        infect.last_y = y;

        if( infect.desinfectTimer < 0 )
        {
            infect.desinfectTimer = 0;
        }
    }

    void render( const secs::Entity& e ) override
    {
        auto& infect = m_world.component<InfectComponent>(e);

        bool must_show =
                ( infect.desinfect &&  m_mapScene.isInfected(infect.last_x, infect.last_y))
             || (!infect.desinfect && !m_mapScene.isInfected(infect.last_x, infect.last_y));

        if( infect.desinfectTimer > 0 && must_show)
        {
            auto tp = Vec2i(infect.last_x * 32, infect.last_y * 32);
            float xx = infect.desinfectTimer * 16 / infect.desinfectDuration;
            al_draw_filled_rectangle(tp.x() + 2, tp.y() + 2, tp.x() + xx + 2, tp.y() + 2 + 2, al_map_rgb(0, 255, 0));
        }
    }

private:
    secs::Engine& m_world;
    MapScene& m_mapScene;

};
