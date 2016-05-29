#ifndef GADGET_H
#define GADGET_H

#include <memory>
#include <secs/engine.h>

class Gadget
{
public:

	typedef std::shared_ptr<Gadget> SharedPtr;

	Gadget( secs::Engine& world );
	virtual ~Gadget() = 0 ;
	virtual void fire( const secs::Entity& caster ) = 0 ;

protected:
	secs::Engine& world();

private:
	secs::Engine& m_world;

};

#endif // GADGET_H
