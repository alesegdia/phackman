#pragma once

#include <secs/secs.h>
#include "../component/components.h"
#include "../../ai/blackboard.h"


class MapNavigationSystem : public secs::EntitySystem
{
public:

	MapNavigationSystem( secs::Engine& world )
		: m_world(world)
	{
		setNeededComponents<TransformComponent,
							MapAgentInputComponent,
							MapAgentStateComponent,
							RenderFacingComponent>();
	}

	void process( float delta, const secs::Entity &e ) override
	{
		auto& agtinput_comp = m_world.component<MapAgentInputComponent>(e);

		if( agtinput_comp.inputRequested )
		{
			auto& transform_comp = m_world.component<TransformComponent>(e);
			auto& agtstate_comp = m_world.component<MapAgentStateComponent>(e);
			auto& facing_comp = m_world.component<RenderFacingComponent>(e);

			PathNode::SharedPtr my_node = Blackboard::instance.navigationMap->getNodeAt(
						transform_comp.position.x(),
						transform_comp.position.y() );

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

			if( agtstate_comp.lastNode != nullptr && agtstate_comp.lastNode->getNeighboor( facing_comp.facing ) )
			{
				float nx, ny;

				switch( facing_comp.facing )
				{
				case Up:
					nx = agtstate_comp.lastNode->x() * 16;
					ny = transform_comp.position.y() - delta * 60;
					break;
				case Right:
					nx = transform_comp.position.x() + delta * 60;
					ny = agtstate_comp.lastNode->y() * 16;
					break;
				case Down:
					nx = agtstate_comp.lastNode->x() * 16;
					ny = transform_comp.position.y() + delta * 60;
					break;
				case Left:
					nx = transform_comp.position.x() - delta * 60;
					ny = agtstate_comp.lastNode->y() * 16;
					break;
				}

				transform_comp.position.set( nx, ny );
			}
		}
	}

private:
	secs::Engine& m_world;

};
