#pragma once

#include <functional>

struct DieOnStopComponent
{
    float last_x, last_y;
    std::function<void(void)> onDeath;

};
