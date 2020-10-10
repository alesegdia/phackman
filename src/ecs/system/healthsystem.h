#pragma once

#include <secs/secs.h>
#include "../components.h"


class HealthSystem : public secs::TypedEntitySystem<HealthComponent>
{
public:

    void process( double delta, const secs::Entity &e, HealthComponent& hc ) override
    {
        SECS_UNUSED(delta);
        if( hc.currentHealth <= 0 && !hasComponent<DieComponent>(e))
        {
            addComponent<DieComponent>(e);
        }
    }

    void onAdded(const secs::Entity& e) override
    {
        auto& hc = component<HealthComponent>(e);
        hc.currentHealth = hc.maxHealth;
    }

};

