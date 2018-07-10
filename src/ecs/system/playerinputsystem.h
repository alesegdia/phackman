#pragma once

#include <secs/secs.h>
#include <alligator/input/input.h>
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
		u = Input::IsKeyDown( ALLEGRO_KEY_UP );
		d = Input::IsKeyDown( ALLEGRO_KEY_DOWN );
		r = Input::IsKeyDown( ALLEGRO_KEY_RIGHT );
		l = Input::IsKeyDown(ALLEGRO_KEY_LEFT);
		space = Input::IsKeyDown(ALLEGRO_KEY_SPACE);
        agtinput_comp.requestedDesinfect = Input::IsKeyDown(ALLEGRO_KEY_C);
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

        auto& tlc = component<TileComponent>(e);
        auto& tc = component<TransformComponent>(e);

        if( Input::IsKeyJustPressed( ALLEGRO_KEY_W ) )
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
