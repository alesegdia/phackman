#pragma once

#include <aether/aether.h>

struct PowerConsumerComponent
{
    bool powered = true;
	const aether::graphics::TextureRegion* unpowered_asset = nullptr;
};
