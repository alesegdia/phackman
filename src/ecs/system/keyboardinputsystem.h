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
		setNeededComponents<KeyboardInputComponent, FacingComponent>();
	}

	void process( float delta, const secs::Entity &e ) override
	{
		auto& facing_comp = m_world.component<FacingComponent>(e);

		if( Input::IsKeyDown( ALLEGRO_KEY_LEFT ) )
		{
			facing_comp.facing = FacingComponent::Facing::Left;
		}
		else if( Input::IsKeyDown( ALLEGRO_KEY_RIGHT ) )
		{
			facing_comp.facing = FacingComponent::Facing::Right;
		}

		if( Input::IsKeyDown( ALLEGRO_KEY_UP ) )
		{
			facing_comp.facing = FacingComponent::Facing::Up;
		}
		if( Input::IsKeyDown( ALLEGRO_KEY_DOWN ) )
		{
			facing_comp.facing = FacingComponent::Facing::Down;
		}

	}

private:
	secs::Engine& m_world;

};
