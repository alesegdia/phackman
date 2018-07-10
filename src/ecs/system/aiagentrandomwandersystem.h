#pragma once

#include <secs/secs.h>
#include "../components.h"
#include "../../ai/blackboard.h"


class AIAgentRandomWanderSystem : public secs::TypedEntitySystem<
        TransformComponent,
        AIAgentRandomWanderComponent,
        AgentInputComponent>
{
public:
    void process( double delta, const secs::Entity &e,
                  TransformComponent& transf_comp,
                  AIAgentRandomWanderComponent& wander_comp,
                  AgentInputComponent& ainput_comp) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        PathNode::SharedPtr my_node = Blackboard::instance.navigationMap->getNodeAt( transf_comp.position.x(), transf_comp.position.y() );
        if( my_node != nullptr && wander_comp.lastNodeDecided != my_node )
        {
            Facing next_facing = my_node->facings()[rand() % my_node->facings().size()];
            wander_comp.lastNodeDecided = my_node;
            ainput_comp.requestedFacing = next_facing;
            ainput_comp.inputRequested = true;
        }
    }
};
