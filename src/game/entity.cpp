#include "entity.h"

Entity::Entity(float x, float y)
	: m_x(x), m_y(y)
{

}

float Entity::x()
{
	return m_x;
}

float Entity::y()
{
	return m_y;
}
