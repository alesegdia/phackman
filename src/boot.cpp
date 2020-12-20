#include <aether/aether.h>
#include "game/gameplayscreen.h"
#include "game/assets.h"

std::shared_ptr<aether::core::IScreen> aether_boot_screen()
{
	Assets::Initialize();
	return std::make_shared<GameplayScreen>();
}
