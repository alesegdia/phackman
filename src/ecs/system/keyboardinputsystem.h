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
		auto& agtinput_comp = m_world.component<AgentInputComponent>(e);

		bool u, d, r, l, space;
		u = Input::IsKeyDown( ALLEGRO_KEY_UP );
		d = Input::IsKeyDown( ALLEGRO_KEY_DOWN );
		r = Input::IsKeyDown( ALLEGRO_KEY_RIGHT );
		l = Input::IsKeyDown(ALLEGRO_KEY_LEFT);
		space = Input::IsKeyDown(ALLEGRO_KEY_SPACE);

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
	}

private:
	secs::Engine& m_world;

};
