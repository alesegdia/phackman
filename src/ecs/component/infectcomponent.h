#pragma once

struct InfectComponent
{
    bool desinfect = false;
    float desinfectTimer = 1;
    float desinfectDuration = 1;

    int last_x = 0;
    int last_y = 0;

};
