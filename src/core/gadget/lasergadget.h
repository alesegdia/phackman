#ifndef LASERGADGET_H
#define LASERGADGET_H

#include "gadget.h"

class LaserGadget : public Gadget
{
public:
	LaserGadget();

	// Gadget interface
	void fire(const secs::Entity &caster) override ;

};

#endif // LASERGADGET_H
