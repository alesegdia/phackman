#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

#include "gameplayscreen.h"
#include "assets.h"
#include "../constants.h"
#include <filesystem>

//#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen()
    : m_cam(new aether::graphics::Camera({Constants::WindowWidth, Constants::WindowHeight})), m_guiCam(new aether::graphics::Camera())
{

}

int GameplayScreen::Load()
{
    gw = std::make_shared<GameWorld>();
    gw->step(0);
    m_scroll.Setup(m_cam, aether::math::Rectf(0, 0, gw->mapSize().GetX() * 16, gw->mapSize().GetY() * 16));
    return 0;
}

void GameplayScreen::Update(uint64_t delta)
{
	//m_player->update(delta);
    if( aether::core::is_key_down(aether::core::KeyCode::Escape) )
	{
        RequestCloseApp();
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

void GameplayScreen::Render()
{
    auto new_pos = gw->playerPos();

    m_cam->SetScale(m_scale, m_scale);
    m_scroll.Focus(new_pos.GetX() + 16, new_pos.GetY() + 16);

    aether::graphics::clear(0,0,0);
    gw->Render();

    m_guiCam->SetScale(m_scale, m_scale);
    m_guiCam->SetPosition(0, 0);
    m_guiCam->Bind();

    Assets::instance->maptilesSheet->GetFrame(26)->Draw(0, 0);
    Assets::instance->maptilesSheet->GetFrame(27)->Draw(0,16);
    Assets::instance->maptilesSheet->GetFrame(28)->Draw(0,32);

    const auto& rsc = gw->playerResourceStorageComponent();
    char rc[4]; char ic[4]; char pc[4];
    sprintf(rc, "%d", rsc.reinforceCells);
    sprintf(ic, "%d", rsc.industryCells);
    sprintf(pc, "%d", rsc.powerCells);
    Assets::instance->guiFont.Print(rc, 18,  0, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont.Print(ic, 18, 16, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont.Print(pc, 18, 32, aether::graphics::Color(1.0f, 1.0f, 1.0f));

    if (m_pause)
    {
        aether::graphics::draw_filled_rectangle(0, 0, 1000, 1000, aether::graphics::Color(0.0f, 0.0f, 0.0f, 0.5f));
        Assets::instance->guiFont.Print("GAME PAUSED\n<P> = pause/unpause\n<ARROWS> = move phackman\n<SPACE> = shoot\n<C> = desinfect/reinforce\n<V> = build turret",
            Constants::WindowWidth / (m_scale * 2), Constants::WindowHeight / (m_scale * 2) - 10 * m_scale,
            300.0f, 15.0f,
            aether::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f), false);
    }
}

int GameplayScreen::Unload()
{
	Assets::Dispose();
	return 0;
}


