#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
#include "../components.h"


class PlayerInputSystem : public secs::EntitySystem
{
public:

    PlayerInputSystem()
	{
        setNeededComponents<PlayerInputComponent,
							AgentInputComponent>();
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
		u = Input::IsKeyDown( ALLEGRO_KEY_UP );
		d = Input::IsKeyDown( ALLEGRO_KEY_DOWN );
		r = Input::IsKeyDown( ALLEGRO_KEY_RIGHT );
		l = Input::IsKeyDown(ALLEGRO_KEY_LEFT);
		space = Input::IsKeyDown(ALLEGRO_KEY_SPACE);
        agtinput_comp.requestedDesinfect = Input::IsKeyDown(ALLEGRO_KEY_X);
        agtinput_comp.requestedReinforce = Input::IsKeyJustPressed(ALLEGRO_KEY_C);

        if( agtinput_comp.requestedDesinfect )
        {
            auto& ic = processor()->addComponent<InfectComponent>(e);
            ic.desinfect = true;
            agtinput_comp.speed = agtinput_comp.lower_speed;
        }
        else
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

        if( Input::IsKeyDown( ALLEGRO_KEY_W ) )
        {
            processor()->addComponent<WallPlacementComponent>(e);
        }
	}

    bool inhibit = false;

};
