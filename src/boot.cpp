#include <aether/aether.h>
#include "game/gameplayscreen.h"
#include "game/assets.h"

#include <aether/platform.h>

std::shared_ptr<aether::core::Application> aether_create_app()
{
	return std::make_shared<aether::core::Application>(800, 600);
}

std::shared_ptr<aether::core::IScreen> aether_boot_screen()
{
	Assets::Initialize();
	return std::make_shared<GameplayScreen>();
}
