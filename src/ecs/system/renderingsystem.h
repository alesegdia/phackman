#pragma once

#include <secs/secs.h>
#include "../component/components.h"

class RenderingSystem : public secs::EntitySystem
{
public:

	RenderingSystem( secs::Engine& world );

    void process(double delta, const secs::Entity &e) override;

private:
	secs::Engine& m_world;

};
