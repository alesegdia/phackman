
#include <allegro5/allegro_primitives.h>

#include "entity.h"

Entity::Entity(float x, float y, NavigationMap::SharedPtr navmap)
	: m_position(x, y), m_navmap(navmap)
{

}

void Entity::update(double delta)
{
	m_animData.timer += delta;

	if( m_canMove )
	{
		handleMovement(delta);
	}
}

void Entity::handleMovement(double delta)
{
	float nx, ny;

	PathNode::SharedPtr my_node = m_navmap->getNodeAt(m_position.x , m_position.y );

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
			ny = m_position.y - delta * m_speed;
			break;
		case Direction::RIGHT:
			nx = m_position.x + delta * m_speed;
			ny = m_lastNode->y() * 16;
			break;
		case Direction::DOWN:
			nx = m_lastNode->x() * 16;
			ny = m_position.y + delta * m_speed;
			break;
		case Direction::LEFT:
			nx = m_position.x - delta * m_speed;
			ny = m_lastNode->y() * 16;
			break;
		case Direction::NONE:
			assert(false);
			break;
		}

		m_position.x = nx;
		m_position.y = ny;
	}
}

void Entity::render()
{
	if( ENABLE_DEBUG )
	{
		al_draw_filled_rectangle(m_position.x, m_position.y, m_position.x + 32, m_position.y + 32, al_map_rgb(255,0,0));
	}

	if( m_anim != nullptr )
	{
		m_anim->updateData(m_animData);

		ALLEGRO_BITMAP* frame = m_animData.currentFrame;

		float cx = static_cast<float>(al_get_bitmap_width(frame)) / 2.f;
		float cy = static_cast<float>(al_get_bitmap_height(frame)) / 2.f;

		float angle;
		switch( m_facing )
		{
		case UP:	angle = 0; break;
		case RIGHT:	angle = M_PI_2; break;
		case DOWN:	angle = M_PI; break;
		case LEFT:  angle = -M_PI_2; break;
		default:	angle = 0; break;
		}

		al_draw_rotated_bitmap(frame, cx, cy, m_position.x + cx, m_position.y + cy, angle, 0 );
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

void Entity::setEnableMovement(bool enable)
{
	m_canMove = enable;
}

