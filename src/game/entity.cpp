
#include <allegro5/allegro_primitives.h>

#include "entity.h"
#include "../core/input.h"

Entity::Entity(float x, float y, NavigationMap::SharedPtr navmap)
	: m_x(x), m_y(y), m_navmap(navmap)
{

}

void Entity::update(double delta)
{
	m_animData.timer += delta;
	handleMovement(delta);
}

void Entity::handleMovement(double delta)
{
	float nx, ny;

	PathNode::SharedPtr my_node = m_navmap->getNodeAt(m_x , m_y );

	// middle of a path
	if( my_node == nullptr )
	{
		// path turn
		if( (get_orientation(m_requestedFacing) == get_orientation(m_facing)) && (m_requestedFacing != m_facing) )
		{
			m_facing = m_requestedFacing;
			PathNode::SharedPtr n = this->m_lastNode;
			m_lastNode = m_targetNode;
			m_targetNode = n;
		}
	}
	// over a node
	else
	{
		m_lastNode = my_node;
		PathNode::SharedPtr target_node = m_lastNode->getNeighboor(m_requestedFacing);
		if( target_node != nullptr )
		{
			m_facing = m_requestedFacing;
			m_targetNode = target_node;
		}

	}

	// apply movement
	if( m_lastNode != nullptr && m_lastNode->getNeighboor(m_facing) )
	{
		switch(m_facing)
		{
		case Direction::UP:
			nx = m_lastNode->x() * 16;
			ny = m_y - delta * m_speed;
			break;
		case Direction::RIGHT:
			nx = m_x + delta * m_speed;
			ny = m_lastNode->y() * 16;
			break;
		case Direction::DOWN:
			nx = m_lastNode->x() * 16;
			ny = m_y + delta * m_speed;
			break;
		case Direction::LEFT:
			nx = m_x - delta * m_speed;
			ny = m_lastNode->y() * 16;
			break;
		case Direction::NONE:
			assert(false);
			break;
		}

		m_x = nx;
		m_y = ny;
	}
}

void Entity::render()
{
	if( ENABLE_DEBUG )
	{
		al_draw_filled_rectangle(m_x, m_y, m_x + 32, m_y + 32, al_map_rgb(255,0,0));
	}

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
