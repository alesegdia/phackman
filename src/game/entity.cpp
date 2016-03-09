#include "entity.h"

Entity::Entity(float x, float y, std::shared_ptr<Animation> anim)
	: m_x(x), m_y(y), m_anim(anim)
{

}

void Entity::update(double delta)
{
	m_animData.timer += delta;
}

void Entity::render()
{
	if( m_anim != nullptr )
	{
		m_anim->updateData(m_animData);
		al_draw_bitmap(m_animData.currentFrame, m_x, m_y, 0);
	}
}
