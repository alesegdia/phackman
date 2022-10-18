#pragma once

#include <secs/secs.h>
#include "../components.h"


class HealthSystem : public secs::TypedEntitySystem<HealthComponent>
{
public:

    void process( double delta, const secs::Entity &e, HealthComponent& hc ) override
    {
        SECS_UNUSED(delta);
        if( hc.currentHealth <= 0 && !HasComponent<DieComponent>(e))
        {
            AddComponent<DieComponent>(e);
        }
    }

    void OnEntityAdded(const secs::Entity& e) override
    {
        auto& hc = GetComponent<HealthComponent>(e);
        hc.currentHealth = hc.maxHealth;
    }

};

