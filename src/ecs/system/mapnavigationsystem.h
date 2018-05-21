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

    void process( double delta, const secs::Entity &e ) override
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

			auto facing_neighboor = agtstate_comp.lastNode->getNeighboor( facing_comp.facing );
			if( agtstate_comp.lastNode != nullptr && facing_neighboor != nullptr )
			{
				float nx, ny;
				const float speed = agtinput_comp.speed;
				float displacement = float(delta * speed);
				
				const Vec2f np = Vec2f(facing_neighboor->x() * 16, facing_neighboor->y() * 16);
				const Vec2f p = transform_comp.position;
				
				float neighboor_dist = abs((np.x() - p.x()) + (np.y() - p.y()));
				float odisp = displacement;
				displacement = displacement < neighboor_dist ? displacement : neighboor_dist;

				// ahora mismo la entidad va dando saltitos en cada nodo porque se ajusta siempre la posici�n al nodo
				// para arreglar esto, miraremos hasta qu� nodo podemos llegar con el desplazamiento indicado y
				// haremos toda la comprobaci�n con ese nodo, en lugar de simplemente con el siguiente

				switch (facing_comp.facing)
				{
				case Up:
					nx = agtstate_comp.lastNode->x() * 16;
					ny = transform_comp.position.y() - displacement;
					break;
				case Right:
					nx = transform_comp.position.x() + displacement;
					ny = agtstate_comp.lastNode->y() * 16;
					break;
				case Down:
					nx = agtstate_comp.lastNode->x() * 16;
					ny = transform_comp.position.y() + displacement;
					break;
				case Left:
					nx = transform_comp.position.x() - displacement;
					ny = agtstate_comp.lastNode->y() * 16;
					break;
				}

				transform_comp.position.set(nx, ny);
			}
		}
	}

private:
	secs::Engine& m_world;

};
