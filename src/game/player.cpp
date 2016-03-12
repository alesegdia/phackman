#include "player.h"
#include "../core/input.h"

Player::Player(float x, float y, NavigationMap::SharedPtr navmap)
	: Entity(x, y, navmap)
{
	setAnim(Assets::instance->phackmanWalk);
}

void Player::update(double delta)
{
	Entity::update(delta);

	if( Input::IsKeyDown(ALLEGRO_KEY_LEFT) )
	{
		setRequestedFacing(Direction::LEFT);
	}
	else if( Input::IsKeyDown(ALLEGRO_KEY_RIGHT) )
	{
		setRequestedFacing(Direction::RIGHT);
	}
	else if( Input::IsKeyDown(ALLEGRO_KEY_DOWN) )
	{
		setRequestedFacing(Direction::DOWN);
	}
	else if( Input::IsKeyDown(ALLEGRO_KEY_UP) )
	{
		setRequestedFacing(Direction::UP);
	}
}
