#include "entity.h"

Entity::Entity(float x, float y, std::shared_ptr<Animation> anim)
	: m_x(x), m_y(y), m_anim(anim)
{

}
