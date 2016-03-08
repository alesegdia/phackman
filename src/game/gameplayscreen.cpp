#include <allegro5/allegro.h>
#include <iostream>

#include "gameplayscreen.h"
#include "game.h"
#include "assets.h"
#include "../core/matrix.h"
#include "../mapgen/mapgen.h"

GameplayScreen::GameplayScreen( Game* g )
{
	m_game = g;
}

GameplayScreen::~GameplayScreen()
{

}

void GameplayScreen::wake()
{
	std::shared_ptr<Matrix2Di> map = LayoutBuilder().generate(ShapeStorage().makeSample());
	Matrix2DDebug<int>() << *map;
}

void GameplayScreen::update(double delta)
{
	ad.timer += ((float)delta);
}

void GameplayScreen::render()
{
	al_clear_to_color(al_map_rgb(20,20,20));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	Assets::instance->characterAnim->updateData(ad);

	al_draw_bitmap(ad.currentFrame, 0, 0, 0);
}
