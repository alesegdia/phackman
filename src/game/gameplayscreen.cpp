#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "gameplayscreen.h"
#include "assets.h"
#include "../constants.h"

//#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen()
    : m_cam(new aether::graphics::Camera()), m_guiCam(new aether::graphics::Camera())
{

}

void GameplayScreen::show()
{
    gw = std::make_shared<GameWorld>();
    gw->step(0);
}

void GameplayScreen::update(uint64_t delta)
{
	//m_player->update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
	{
		//m_game->close();
	}

    if( aether::core::is_key_down(aether::core::KeyCode::K1) )
    {
        m_scale = 1;
    }

    if( aether::core::is_key_down(aether::core::KeyCode::K2) )
    {
        m_scale = 2;
    }

    if( aether::core::is_key_down(aether::core::KeyCode::K3) )
    {
        m_scale = 3;
    }

    if( aether::core::is_key_just_pressed(aether::core::KeyCode::P) )
    {
        m_pause = ! m_pause;
    }

    if( false == m_pause )
    {
        gw->step(double(delta));

        if( gw->isGameOver() )
        {
            gw = std::make_shared<GameWorld>();
            gw->step(0);
        }
    }

    if( aether::core::is_key_just_pressed(aether::core::KeyCode::R) )
    {
        gw = std::make_shared<GameWorld>();
        gw->step(0);
    }
}

void GameplayScreen::render()
{
    auto new_pos = gw->playerPos();

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

    aether::graphics::clear(0,0,0);
    gw->render();

    m_guiCam->scale(m_scale, m_scale);
    m_guiCam->position(0, 0);
    m_guiCam->bind();

    Assets::instance->maptilesSheet->getFrame(26)->draw(0, 0);
    Assets::instance->maptilesSheet->getFrame(27)->draw(0,16);
    Assets::instance->maptilesSheet->getFrame(28)->draw(0,32);

    const auto& rsc = gw->playerResourceStorageComponent();
    char rc[4]; char ic[4]; char pc[4];
    sprintf(rc, "%d", rsc.reinforceCells);
    sprintf(ic, "%d", rsc.industryCells);
    sprintf(pc, "%d", rsc.powerCells);
    Assets::instance->guiFont.print(rc, 18,  0, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont.print(ic, 18, 16, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont.print(pc, 18, 32, aether::graphics::Color(1.0f, 1.0f, 1.0f));

    if (m_pause)
    {
        aether::graphics::draw_filled_rectangle(0, 0, 1000, 1000, aether::graphics::Color(0.0f, 0.0f, 0.0f, 0.5f));
        Assets::instance->guiFont.print("GAME PAUSED\n<P> = pause/unpause\n<ARROWS> = move phackman\n<SPACE> = shoot\n<C> = desinfect/reinforce\n<V> = build turret",
            Constants::WindowWidth / (m_scale * 2), Constants::WindowHeight / (m_scale * 2) - 10 * m_scale,
            300.0f, 15.0f,
            aether::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f), false);
    }
}

void GameplayScreen::hide()
{

}


