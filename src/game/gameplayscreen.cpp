#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/input/input.h>
#include <iostream>

#include "gameplayscreen.h"
#include "phackmangame.h"
#include "assets.h"
#include <alligator/util/matrix.h>
#include "../map/mapgen.h"
#include "../ai/pfmap.h"
#include "../ai/blackboard.h"
#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen( PhackmanGame* g )
    : m_game(g), m_cam(new Camera())
{

}

GameplayScreen::~GameplayScreen()
{

}

void GameplayScreen::show()
{
	m_map = LayoutBuilder().generate(ShapeStorage().makeSample());
	m_tileMap = convolute3x3(*m_map, draw_map_tiles_convolutor);
	m_navmap.reset(new NavigationMap(m_map));
	Blackboard::instance.navigationMap = m_navmap;

	auto start_node = m_navmap->nodes()[0];

    secs::Entity player = gw.factory().makePlayer((start_node->x()) * 16, (start_node->y()) * 16);
    TransformComponent& tc = gw.engine().component<PositionComponent>(player);

    m_playerPositionComponent = &tc;

}

void GameplayScreen::update(double delta)
{
	//m_player->update(delta);
	if( Input::IsKeyDown(ALLEGRO_KEY_ESCAPE) )
	{
		m_game->close();
	}

    if( Input::IsKeyDown(ALLEGRO_KEY_F1) )
    {
        m_shownodes = !m_shownodes;
    }

    if( Input::IsKeyDown(ALLEGRO_KEY_F2) )
    {
        m_showsolid = !m_showsolid;
    }

	gw.step( static_cast<float>(delta) );
}

void GameplayScreen::render()
{
    m_cam->position(m_player, 0);
    m_cam->scale(1, 1);
    m_cam->bind();
	al_clear_to_color(al_map_rgb(20,20,20));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

	//debugRender();
	tilesRender();
	//m_player->render();
	gw.render();

    if( m_shownodes )
    {
        for( PathNode::SharedPtr node : m_navmap->nodes() )
        {
            float x, y;
            x = (node->x()+1) * 16;
            y = (node->y()+1) * 16;
            al_draw_ellipse( x, y, 4, 4, al_map_rgb(255, 255, 0), 1);
        }
    }

    if( m_showsolid )
    {
        MapSolidDebug(m_tileMap).render();
    }
}

void GameplayScreen::hide()
{

}

void GameplayScreen::tilesRender()
{
	for( int r = 0; r < m_tileMap->rows(); r++ )
	{
		for( int c = 0; c < m_tileMap->cols(); c++ )
		{
			int x1, y1, x2, y2;
			x1 = c * 16; y1 = r * 16;
			x2 = (c+1) * 16; y2 = (r+1) * 16;

			ALLEGRO_BITMAP* bm = Assets::instance->maptilesSheet->getFrame(m_tileMap->get(c, r));
			al_draw_bitmap(bm, x1, y1, 0);
		}
	}
}

void GameplayScreen::debugRender()
{
	for( int r = 0; r < m_map->rows(); r++ )
	{
		for( int c = 0; c < m_map->cols(); c++ )
		{
			int x1, y1, x2, y2;
			x1 = c * 16; y1 = r * 16;
			x2 = (c+1) * 16; y2 = (r+1) * 16;

			if( m_map->get(c, r) == 1 )
			{
				al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0));
			}
			else
			{
				al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 255));
			}
		}
	}

	for( PathNode::SharedPtr node : m_navmap->nodes() )
	{
		float cx, cy;
		cx = (node->x()+1) * 16;
		cy = (node->y()+1) * 16;

		for( PathNode::SharedPtr neighboor : node->neighboors() )
		{
			int ncx, ncy;
			ncx = (neighboor->x()+1) * 16;
			ncy = (neighboor->y()+1) * 16;

			al_draw_line(cx, cy, ncx, ncy, al_map_rgba(0, 255, 255, 2), 1);
		}

		al_draw_filled_circle(cx, cy, 3, al_map_rgb(255, 0, 0));
	}
}
