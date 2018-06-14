#pragma once

#include <stdint.h>
#include <assert.h>

#include "../../core/facing.h"

struct MapAwarenessComponent
{
    bool sensorGroups[2][4];

    bool getDirectionSensor( int group, Facing direction )
    {
        validateInput(group, direction);
        return sensorGroups[group][int(direction)];
    }

    bool setDirectionSensor( int group, Facing direction, bool value )
    {
        validateInput(group, direction);
        sensorGroups[group][int(direction)] = value;
    }

    void validateInput( int group, Facing direction )
    {
        assert(group >= 0 && group < 2);
        assert(direction != Facing::None);
    }

};
