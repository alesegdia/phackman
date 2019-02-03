#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <alligator/input/input.h>
#include <iostream>

#include "gameplayscreen.h"
#include "phackmangame.h"
#include "assets.h"
#include <alligator/util/matrix.h>
#include "../constants.h"

//#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen( PhackmanGame* g )
    : m_game(g), m_cam(new Camera()), m_guiCam(new Camera())
{

}

void GameplayScreen::show()
{
    gw = std::make_shared<GameWorld>();
    gw->step(0);
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

    if( Input::IsKeyJustPressed(ALLEGRO_KEY_P) )
    {
        m_pause = ! m_pause;
    }

    if( false == m_pause )
    {
        gw->step(delta);

        if( gw->isGameOver() )
        {
            gw = std::make_shared<GameWorld>();
            gw->step(0);
            m_pause = true;
        }
    }
}

void GameplayScreen::render()
{
    auto new_pos = gw->playerPos();


    //std::cout << new_pos.x() << "," << new_pos.y() << std::endl;

    float xmin = Constants::WindowWidth/4.f;
    float xmax = gw->mapSize().x() * 16 - Constants::WindowWidth/4.f;
    new_pos.x(std::max(std::min(new_pos.x(), xmax), xmin));

    float ymin = Constants::WindowHeight/4.f;
    float ymax = gw->mapSize().y() * 16 - Constants::WindowHeight/4.f;
    new_pos.y(std::max(std::min(new_pos.y(), ymax), ymin));

    new_pos.x(-floor(new_pos.x()) * m_scale + Constants::WindowWidth/2);
    new_pos.y(-floor(new_pos.y()) * m_scale + Constants::WindowHeight/2);

	m_cam->position(new_pos.x(), new_pos.y());
    m_cam->scale(m_scale, m_scale);
    m_cam->bind();

	al_clear_to_color(al_map_rgb(20,20,20));
	al_set_target_bitmap(al_get_backbuffer(m_game->display()));

    gw->render();

    m_guiCam->scale(m_scale, m_scale);
    m_guiCam->position(0, 0);
    m_guiCam->bind();

    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(26), 0,  0, 0);
    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(27), 0, 16, 0);
    al_draw_bitmap(Assets::instance->maptilesSheet->getFrame(28), 0, 32, 0);

    const auto& rsc = gw->playerResourceStorageComponent();
    char rc[4]; char ic[4]; char pc[4];
    sprintf(rc, "%d", rsc.reinforceCells);
    sprintf(ic, "%d", rsc.industryCells);
    sprintf(pc, "%d", rsc.powerCells);
    al_draw_text(Assets::instance->guiFont, al_map_rgb(255,255,255), 18, 0, 0, rc);
    al_draw_text(Assets::instance->guiFont, al_map_rgb(255,255,255), 18, 16, 0, ic);
    al_draw_text(Assets::instance->guiFont, al_map_rgb(255,255,255), 18, 32, 0, pc);
}

void GameplayScreen::hide()
{

}


