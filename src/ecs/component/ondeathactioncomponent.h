#pragma once

#include <functional>
#include <secs/secs.h>

struct OnDeathActionComponent
{
    using Action = std::function<void(const secs::Entity& e)>;
    Action action;
};
