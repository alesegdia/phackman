#include "player.h"
#include <alligator/input/input.h>

Player::Player(float x, float y, NavigationMap::SharedPtr navmap)
	: Entity(x, y, navmap)
{
	setAnim(Assets::instance->phackmanWalk);
}

void Player::update(double delta)
{
	Entity::update(delta);

	bool u, d, l, r;
	u = Input::IsKeyDown(ALLEGRO_KEY_UP);
	d = Input::IsKeyDown(ALLEGRO_KEY_DOWN);
	l = Input::IsKeyDown(ALLEGRO_KEY_LEFT);
	r = Input::IsKeyDown(ALLEGRO_KEY_RIGHT);

	setEnableMovement( u | d | l | r );

	if( l )
	{
		setRequestedFacing(Direction::LEFT);
	}
	else if( r )
	{
		setRequestedFacing(Direction::RIGHT);
	}
	else if( d )
	{
		setRequestedFacing(Direction::DOWN);
	}
	else if( u )
	{
		setRequestedFacing(Direction::UP);
	}
}
