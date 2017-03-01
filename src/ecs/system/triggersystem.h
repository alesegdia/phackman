#ifndef TRIGGERSYSTEM_H
#define TRIGGERSYSTEM_H

#include <secs/secs.h>

#include "../component/components.h"

class TriggerSystem : public secs::TypedEntitySystem<TriggerComponent>
{
public:
	TriggerSystem();
};

#endif // TRIGGERSYSTEM_H
