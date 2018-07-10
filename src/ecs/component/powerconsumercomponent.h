#pragma once

#include <allegro5/allegro.h>

struct PowerConsumerComponent
{
    bool powered = true;
    ALLEGRO_BITMAP* unpowered_asset = nullptr;
};
