#pragma once

#include <secs/secs.h>
#include "../components.h"
#include "../../ai/blackboard.h"
#include "../../map/mapscene.h"

class MapNavigationSystem : public secs::EntitySystem
{
public:

    MapNavigationSystem( MapScene& map_scene )
        : m_mapScene(map_scene)
    {
        SetNeededComponents<TransformComponent,
                            AgentInputComponent,
                            AgentMapStateComponent,
                            RenderFacingComponent>();
    }

    void Process( double delta, const secs::Entity &e ) override
    {
        auto& agtinput_comp = GetComponent<AgentInputComponent>(e);

        if (agtinput_comp.requestedAttack)
        {
            return;
        }

        bool do_process = true;
        if (m_activateDebug)
        {
            static float accumulated_time = 0;
            accumulated_time += delta;
            const float time_to_process = 0.f;
            do_process = accumulated_time >= time_to_process;
            if (do_process) {
                accumulated_time -= time_to_process;
            }
        }

        if( do_process && agtinput_comp.inputRequested )
        {

            auto& transform_comp = GetComponent<TransformComponent>(e);
            auto& agtstate_comp = GetComponent<AgentMapStateComponent>(e);
            auto& facing_comp = GetComponent<RenderFacingComponent>(e);

            // get node at my position
            PathNode::SharedPtr my_node = Blackboard::instance.navigationMap->getNodeAt(
                        transform_comp.position.GetX(),
                        transform_comp.position.GetY() );

            // if I'm in a node
            if( my_node == nullptr )
            {
                Orientation requested_orientation = get_orientation( agtinput_comp.requestedFacing );
                Orientation current_orientation = get_orientation( facing_comp.facing );
                if( requested_orientation == current_orientation && agtinput_comp.requestedFacing != facing_comp.facing )
                {
                    facing_comp.facing = agtinput_comp.requestedFacing;
                    PathNode::SharedPtr last_node = agtstate_comp.lastNode;
                    agtstate_comp.lastNode = agtstate_comp.targetNode;
                    agtstate_comp.targetNode = last_node;
                }
            }
            else
            {
                agtstate_comp.lastNode = my_node;
                PathNode::SharedPtr target_node = agtstate_comp.lastNode->getNeighboor( agtinput_comp.requestedFacing );
                if( target_node != nullptr )
                {
                    facing_comp.facing = agtinput_comp.requestedFacing;
                    agtstate_comp.targetNode = target_node;
                }
            }

            PathNode::SharedPtr facing_neighboor = nullptr;
            auto pp = transform_comp.position;
            aether::math::Vec2i p(pp.GetX() / 32.f, pp.GetY() / 32.f);
            if( agtstate_comp.lastNode == nullptr )
            {
                agtstate_comp.lastNode = scanForNode(p, reverseFacing(facing_comp.facing));
            }

            facing_neighboor = agtstate_comp.lastNode->getNeighboor( facing_comp.facing );

            if( agtstate_comp.lastNode != nullptr && facing_neighboor != nullptr )
            {
                // get furthest neighboor
                // a velocidades muy altas, todav�a da comportamientos raros
                // como que se pasa de largo y atraviesa paredes; REVISAR
                if ( agtinput_comp.requestedFacing == facing_comp.facing )
                {
                    while (facing_neighboor->getNeighboor(facing_comp.facing) != nullptr)
                    {
                        facing_neighboor = facing_neighboor->getNeighboor(facing_comp.facing);
                    }
                }

                float nx, ny;
                const float speed = agtinput_comp.speed;
                float displacement = float(delta * speed);

                const aether::math::Vec2f np = aether::math::Vec2f(facing_neighboor->x() * 16, facing_neighboor->y() * 16);
                const aether::math::Vec2f p = transform_comp.position;

                float neighboor_dist = abs((np.GetX() - p.GetX()) + (np.GetY() - p.GetY()));
                displacement = displacement < neighboor_dist ? displacement : neighboor_dist;

                switch (facing_comp.facing)
                {
                case Up:
                    nx = agtstate_comp.lastNode->x() * 16;
                    ny = transform_comp.position.GetY() - displacement;
                    break;
                case Right:
                    nx = transform_comp.position.GetX() + displacement;
                    ny = agtstate_comp.lastNode->y() * 16;
                    break;
                case Down:
                    nx = agtstate_comp.lastNode->x() * 16;
                    ny = transform_comp.position.GetY() + displacement;
                    break;
                case Left:
                    nx = transform_comp.position.GetX() - displacement;
                    ny = agtstate_comp.lastNode->y() * 16;
                    break;
                default: break;
                }

                transform_comp.position.Set(nx, ny);
            }
        }
    }

private:

    PathNode::SharedPtr scanForNode( aether::math::Vec2i p, Facing direction )
    {
        int tile = 0;
        PathNode::SharedPtr n = nullptr;
        while( tile != 1 && n == nullptr )
        {
            tile = m_mapScene.getSolidness(p.GetX(), p.GetY());
            n = m_mapScene.navmap()->getNodeAt(p.GetX() * 32, p.GetY() * 32);
            advanceFromFacing(p, direction);
        }
        return n;
    }

    bool m_activateDebug = false;
    MapScene& m_mapScene;

};
