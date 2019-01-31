#pragma once

#include <allegro5/allegro5.h>

struct RenderComponent
{
	ALLEGRO_BITMAP* bitmap;
    float offset = 0;
};
