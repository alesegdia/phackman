#include "gadget.h"


Gadget::Gadget(secs::Engine &world)
	: m_world(world)
{

}

Gadget::~Gadget()
{

}

secs::Engine &Gadget::world()
{
	return m_world;
}
