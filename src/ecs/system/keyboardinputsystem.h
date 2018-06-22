#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../component/components.h"


class KeyboardInputSystem : public secs::EntitySystem
{
public:

	KeyboardInputSystem( secs::Engine& world )
		: m_world(world)
	{
		setNeededComponents<KeyboardInputComponent,
							RenderFacingComponent,
							AgentInputComponent>();
	}

    void process( double delta, const secs::Entity &e ) override
	{
        SECS_UNUSED(delta);
        if( inhibit )
        {
            return;
        }

        auto& agtinput_comp = m_world.component<AgentInputComponent>(e);

        bool u, d, r, l, space;
		u = Input::IsKeyDown( ALLEGRO_KEY_UP );
		d = Input::IsKeyDown( ALLEGRO_KEY_DOWN );
		r = Input::IsKeyDown( ALLEGRO_KEY_RIGHT );
		l = Input::IsKeyDown(ALLEGRO_KEY_LEFT);
		space = Input::IsKeyDown(ALLEGRO_KEY_SPACE);
        agtinput_comp.requestedDesinfect = Input::IsKeyDown(ALLEGRO_KEY_X);

        if( agtinput_comp.requestedDesinfect )
        {
            auto& ic = m_world.processor().addComponent<InfectComponent>(e);
            ic.desinfect = true;
            agtinput_comp.speed = agtinput_comp.lower_speed;
        }
        else
        {
            m_world.processor().removeComponent<InfectComponent>(e);
            agtinput_comp.speed = agtinput_comp.normal_speed;
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

        if( Input::IsKeyDown( ALLEGRO_KEY_W ) )
        {
            m_world.processor().addComponent<WallPlacementComponent>(e);
        }
	}

    bool inhibit = false;

private:
	secs::Engine& m_world;

};
