#ifndef LASERGADGET_H
#define LASERGADGET_H

#include "skill.h"

class LaserGadget : public Skill
{
public:
	LaserGadget();

	void trigger(secs::Engine &world, const secs::Entity &caster) override
	{

	}

};

#endif // LASERGADGET_H
