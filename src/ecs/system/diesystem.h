#pragma once

#include <secs/secs.h>

#include "../components.h"

class DieSystem : public secs::TypedEntitySystem<DieComponent>
{
public:
    void process(double delta, const secs::Entity &e, DieComponent &dc)
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(dc);
        if( hasComponent<OnDeathActionComponent>(e) )
        {
            auto& odac = component<OnDeathActionComponent>(e);
            odac.action(e);
        }
        if( hasComponent<PlayerInputComponent>(e) )
        {
            m_playerDead = true;
        }
        processor()->removeEntity(e);
    }

    bool isPlayerDead()
    {
        return m_playerDead;
    }

private:
    bool m_playerDead = false;
};
