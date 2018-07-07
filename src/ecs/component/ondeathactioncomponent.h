#pragma once

#include <functional>

struct OnDeathActionComponent
{
    std::function<void(const secs::Entity& e)> action;
};
