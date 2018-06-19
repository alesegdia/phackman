#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/input/input.h>
#include <iostream>

#include "gameplayscreen.h"
#include "phackmangame.h"
#include "assets.h"
#include <alligator/util/matrix.h>
//#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen( PhackmanGame* g )
    : m_game(g), m_cam(new Camera()), m_guiCam(new Camera()), gw(m_mapScene)
{

}

GameplayScreen::~GameplayScreen()
{

}

void GameplayScreen::show()
{
    auto start_node = m_mapScene.navmap()->nodes()[0];

    m_playerEntity = gw.factory().makePlayer((start_node->x()) * 16, (start_node->y()) * 16);

    //gw.factory().makeEnemy(start_node->x() * 16, start_node->y() * 16);
    //gw.factory().makeSpawner(start_node->x() * 16, start_node->y() * 16);

    auto nm = m_mapScene.nodesMap();

    int numnodes = 0;
    for( int i = 0; i < nm->cols(); i++ )
    {
        for( int j = 0; j < nm->rows(); j++ )
        {
            if( numnodes < 0 && i != 0 && j != 0 && i != nm->cols() -1 && j != nm->rows() - 1)
            {
                auto cell = nm->get(i, j);
                int cx, cy;
                cx = i * 32 + 8;
                cy = j * 32 + 8;
                if( cell == 1 )
                {
                    numnodes++;
                    gw.factory().makeIndustryNode( cx, cy );
                }
                else if (cell == 2 )
                {
                    numnodes++;
                    gw.factory().makePowerNode( cx, cy );
                }
            }
        }
    }

	for( int i = 0; i < 10; i++ )
    {
        int idx = rand() % m_mapScene.navmap()->nodes().size();
        auto n = m_mapScene.navmap()->nodes()[idx];
        gw.factory().makeEnemy(n->x() * 16, n->y() * 16);
    }

}

void GameplayScreen::update(double delta)
{
	//m_player->update(delta);
	if( Input::IsKeyDown(ALLEGRO_KEY_ESCAPE) )
	{
		m_game->close();
	}

    if( Input::IsKeyDown(ALLEGRO_KEY_1) )
    {
        m_scale = 1;
    }

    if( Input::IsKeyDown(ALLEGRO_KEY_2) )
    {
        m_scale = 2;
    }

    if( Input::IsKeyDown(ALLEGRO_KEY_3) )
    {
        m_scale = 3;
    }

    gw.step( delta );
}

void GameplayScreen::render()
{
    Vec2f new_pos = gw.engine().component<TransformComponent>(m_playerEntity).position;
    new_pos.x(-floor(new_pos.x()) * m_scale + 400 - 16);
    new_pos.y(-floor(new_pos.y()) * m_scale + 300 - 16);

	m_cam->position(new_pos.x(), new_pos.y());
    m_cam->scale(m_scale, m_scale);
    m_cam->bind();

	al_clear_to_color(al_map_rgb(20,20,20));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

    m_mapScene.render();

    gw.render();

    m_guiCam->scale(1, 1);
    m_guiCam->position(0, 0);
    m_guiCam->bind();

    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(26), 0,  0, 0);
    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(27), 0, 16, 0);
    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(28), 0, 32, 0);
}

void GameplayScreen::hide()
{

}


