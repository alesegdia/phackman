#include "entity.h"
#include "../core/input.h"

Entity::Entity(float x, float y, NavigationMap::SharedPtr navmap)
	: m_x(x), m_y(y), m_navmap(navmap)
{

}

void Entity::update(double delta)
{
	m_animData.timer += delta;

	switch(m_facing)
	{
	case Direction::UP:
		m_y -= delta * m_speed;
		break;
	case Direction::RIGHT:
		m_x += delta * m_speed;
		break;
	case Direction::DOWN:
		m_y += delta * m_speed;
		break;
	case Direction::LEFT:
		m_x -= delta * m_speed;
		break;
	}

	PathNode::SharedPtr my_node = m_navmap->getNodeAt( m_x, m_y );
}

void Entity::render()
{
	if( m_anim != nullptr )
	{
		m_anim->updateData(m_animData);

		ALLEGRO_BITMAP* frame = m_animData.currentFrame;

		float cx, cy, angle;

		switch( m_facing )
		{
		case UP:
			cx = 0; cy = 0; angle = 0;
			break;
		case RIGHT:
			cx = 0;
			cy = ((float)al_get_bitmap_height(frame));
			angle = M_PI_2;
			break;
		case DOWN:
			cx = ((float)al_get_bitmap_width(frame));
			cy = ((float)al_get_bitmap_height(frame));
			angle = M_PI;
			break;
		case LEFT:
			cx = ((float)al_get_bitmap_width(frame));
			cy = 0;
			angle = -M_PI_2;
			break;
		}

		al_draw_rotated_bitmap(frame, cx, cy, m_x, m_y, angle, 0 );
	}
}

void Entity::setAnim(Animation::SharedPtr anim)
{
	m_anim = anim;
	m_animData.timer = 0;
}

void Entity::setRequestedFacing(Direction dir)
{
	m_requestedFacing = dir;
}


Player::Player(float x, float y, NavigationMap::SharedPtr navmap)
	: Entity(x, y, navmap)
{
	setAnim(Assets::instance->characterAnim);
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
