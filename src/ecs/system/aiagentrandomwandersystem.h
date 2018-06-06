#pragma once

#include <secs/secs.h>
#include "../component/components.h"
#include "../../ai/blackboard.h"


class AIAgentRandomWanderSystem : public secs::EntitySystem
{
public:

    AIAgentRandomWanderSystem( secs::Engine& world )
        : m_world(world)
    {
        setNeededComponents<
                TransformComponent,
                AIAgentRandomWanderComponent,
                AgentInputComponent,
                AgentMapStateComponent>();
    }

    void process( double delta, const secs::Entity &e ) override
    {
        auto& transf_comp = m_world.component<TransformComponent>(e);
        auto& wander_comp = m_world.component<AIAgentRandomWanderComponent>(e);
        auto& ainput_comp = m_world.component<AgentInputComponent>(e);
        auto& amapst_comp = m_world.component<AgentMapStateComponent>(e);

        PathNode::SharedPtr my_node = Blackboard::instance.navigationMap->getNodeAt( transf_comp.position.x(), transf_comp.position.y() );
        if( my_node != nullptr && wander_comp.lastNodeDecided != my_node )
        {
            Facing next_facing = my_node->facings()[rand() % my_node->facings().size()];
            wander_comp.lastNodeDecided = my_node;
            ainput_comp.requestedFacing = next_facing;
            ainput_comp.inputRequested = true;
        }
    }

private:
    secs::Engine& m_world;

};
