#include "../src/game/phackmangame.h"
#include "../src/constants.h"

#include <aether/api/aetherapi.h>

aether::core::ApplicationBase* aether_create_app(int width, int height)
{
	return new PhackmanGame(width, height);
}

