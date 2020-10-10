#pragma once

#include <secs/secs.h>
#include <aether/aether.h>
#include "../components.h"

#include "../../map/mapscene.h"

#include "../entityfactory.h"

class PlayerInputSystem : public secs::EntitySystem
{
public:

    PlayerInputSystem(MapScene& map_scene, EntityFactory& factory)
        : m_mapScene(map_scene),
          m_factory(factory)
	{
        setNeededComponents<PlayerInputComponent,
                            AgentInputComponent,
                            TransformComponent>();
	}

    void process( double delta, const secs::Entity &e ) override
	{
        SECS_UNUSED(delta);

        if( inhibit )
        {
            return;
        }

        auto& agtinput_comp = component<AgentInputComponent>(e);

        bool u, d, r, l, space;
        u = aether::core::is_key_down( aether::core::KeyCode::Up );
        d = aether::core::is_key_down( aether::core::KeyCode::Down );
        r = aether::core::is_key_down( aether::core::KeyCode::Right );
        l = aether::core::is_key_down( aether::core::KeyCode::Left );
        space = aether::core::is_key_down(aether::core::KeyCode::Space);
        agtinput_comp.requestedDesinfect = aether::core::is_key_down(aether::core::KeyCode::C);
        agtinput_comp.requestedReinforce = aether::core::is_key_just_pressed(aether::core::KeyCode::C);

        if( agtinput_comp.requestedDesinfect )
        {
            if (!hasComponent<InfectComponent>(e))
            {
                auto& leic = processor()->addComponent<InfectComponent>(e);
                leic.desinfectDuration = 1e6;
                leic.desinfectTimer = 1e6;
            }
            auto& ic = processor()->component<InfectComponent>(e);
            ic.desinfect = true;
            agtinput_comp.speed = agtinput_comp.lower_speed;
        }
        else if(hasComponent<InfectComponent>(e))
        {
            processor()->removeComponent<InfectComponent>(e);
            agtinput_comp.speed = agtinput_comp.normal_speed;
        }

        if( agtinput_comp.requestedReinforce )
        {
            processor()->addComponent<ReinforceComponent>(e);
        }

		if( u )
		{
			agtinput_comp.requestedFacing = Facing::Up;
		}
		else if( d )
		{
			agtinput_comp.requestedFacing = Facing::Down;
		}

		if( l )
		{
			agtinput_comp.requestedFacing = Facing::Left;
		}
		else if( r )
		{
			agtinput_comp.requestedFacing = Facing::Right;
		}

		agtinput_comp.inputRequested = (u | d | l | r) && !space;
		agtinput_comp.requestedAttack = space;

        auto& tlc = component<TileComponent>(e);
        auto& tc = component<TransformComponent>(e);

        if( aether::core::is_key_just_pressed( aether::core::KeyCode::V ) )
        {
            if( m_mapScene.isReinforced(tlc.current.x(), tlc.current.y()) )
            {
                processor()->addComponent<WallPlacementComponent>(e);
            }
            else
            {
                m_factory.makeCountdownText(tc.position.x(), tc.position.y(), "needs power");
            }
        }
	}

    bool inhibit = false;


private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;


};
