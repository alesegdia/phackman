#pragma once

#include <memory>
#include <secs/secs.h>

class Skill
{
public:

	typedef std::shared_ptr<Skill> SharedPtr;

	virtual ~Skill() = 0 ;
	virtual void trigger( secs::Engine& world, const secs::Entity& caster ) = 0 ;

};

