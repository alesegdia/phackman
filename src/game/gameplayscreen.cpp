#include <iostream>

#include "gameplayscreen.h"
#include "assets.h"
#include "../constants.h"
#include <filesystem>
#include <aether/math/tween.h>

#include "nextlevelscreen.h"

namespace
{

    std::map<std::string, std::string> controlsMap = {
        { "move", "<ARROWS> = move" },
        { "pause", "<P> = pause / unpause" },
        { "shoot", "<SPACE> = shoot" },
        { "desinfect", "<C> = desinfect" },
        { "reinforce", "<C> = reinforce" },
        { "buildturret", "<V> = build turret" },
        { "pickcore", "<Z> = pick core" },
        { "normalize", "<C> = remove reinforce" },
        { "needcore", "Pick up core to exit!" },
    };
}

//#include "../debug/mapsoliddebug.h"

GameplayScreen::GameplayScreen()
    : m_cam(new aether::graphics::Camera({Constants::WindowWidth, Constants::WindowHeight})), m_guiCam(new aether::graphics::Camera())
{

}

int GameplayScreen::Load()
{
    m_scene = std::make_shared<aether::scene::Scene>();
    m_gameWorld = std::make_shared<GameWorld>(m_scene);
    m_gameWorld->step(0);
    m_scroll.Setup(m_cam, aether::math::Rectf(0, 0, m_gameWorld->mapSize().GetX() * 16, m_gameWorld->mapSize().GetY() * 16));
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
        m_gameWorld->step(double(delta));

        if(m_gameWorld->isGameOver() )
        {
            Load();
        }
    }

    if( m_gameWorld->DidPlayerEscape() || aether::core::is_key_just_pressed(aether::core::KeyCode::I))
    {
        std::shared_ptr<IScreen> nextScreen = std::make_shared<NextLevelScreen>();
	    GoToScreen(nextScreen);
    }

    if (aether::core::is_key_just_pressed(aether::core::KeyCode::R))
    {
        Load();
    }

//    m_cam->Update(delta);
    m_cam->Update();


    m_contextControls.clear();
    m_contextControls.push_back("move");
    m_contextControls.push_back("pause");
    if (m_gameWorld->IsPlayerInfected() && !m_gameWorld->PlayerHoldsCore())
    {
        m_contextControls.push_back("desinfect");
    }
    else if (m_gameWorld->IsPlayerReinforced() && !m_gameWorld->PlayerHoldsCore())
    {
        m_contextControls.push_back("normalize");
    }
    else if(!m_gameWorld->PlayerHoldsCore() && !m_gameWorld->PlayerHoldsCore())
    {
        m_contextControls.push_back("reinforce");
    }

    if (!m_gameWorld->PlayerHoldsCore())
    {
        m_contextControls.push_back("shoot");
        if (m_gameWorld->IsPlayerReinforced())
        {
            m_contextControls.push_back("buildturret");
        }
    }

    if (m_gameWorld->PlayerOverCrucible() && !m_gameWorld->PlayerHoldsCore())
    {
        m_contextControls.push_back("pickcore");
    }

    if (m_gameWorld->PlayerOverExit())
    {
        m_contextControls.push_back("needcore");
    }

    aether::TimerManager::GetInstance().Update(delta);

}

void GameplayScreen::Render()
{
    auto new_pos = m_gameWorld->playerPos();

    m_cam->SetScale(m_scale, m_scale);
    m_scroll.Focus(new_pos.GetX() + 16, new_pos.GetY() + 16);
    m_cam->Bind();

    aether::graphics::clear(0.f,0.f,0.f);
	m_gameWorld->Render();
	//m_cam->UnBind();

    m_guiCam->SetScale(m_scale, m_scale);
    m_guiCam->SetPosition(0, 0);
    m_guiCam->Bind();

    Assets::instance->maptilesSheet->GetFrame(74)->Draw(0, 0);
    Assets::instance->maptilesSheet->GetFrame(75)->Draw(0,16);
    Assets::instance->maptilesSheet->GetFrame(76)->Draw(0,32);

    const auto& rsc = m_gameWorld->playerResourceStorageComponent();
    char rc[4]; char ic[4]; char pc[4];
    sprintf_s(rc, "%d", rsc.reinforceCells);
    sprintf_s(ic, "%d", rsc.industryCells);
    sprintf_s(pc, "%d", rsc.powerCells);
    Assets::instance->guiFont->Print(rc, 18,  0, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont->Print(ic, 18, 16, aether::graphics::Color(1.0f, 1.0f, 1.0f));
    Assets::instance->guiFont->Print(pc, 18, 32, aether::graphics::Color(1.0f, 1.0f, 1.0f));

    if (m_pause)
    {
        aether::graphics::draw_filled_rectangle(0, 0, 1000, 1000, aether::graphics::Color(0.0f, 0.0f, 0.0f, 0.5f));
        Assets::instance->guiFont->Print("GAME PAUSED\n<P> = pause/unpause\n<ARROWS> = move phackman\n<SPACE> = shoot\n<C> = desinfect/reinforce\n<V> = build turret\n<Z> = pick core",
            Constants::WindowWidth / (m_scale * 2), Constants::WindowHeight / (m_scale * 2) - 10 * m_scale,
            300.0f, 15.0f,
            aether::graphics::Color(1.0f, 1.0f, 1.0f, 1.0f), false);
    }

    //m_guiCam->UnBind();

    if (!m_pause)
    {
        for (int i = 0; i < m_contextControls.size(); i++)
        {
            auto text = controlsMap[m_contextControls[i]];
            Assets::instance->guiFont->Print(text, 350, 240 - i * 12, aether::graphics::Color::White, aether::graphics::Left);
        }
    }

}

int GameplayScreen::Unload()
{
    aether::TimerManager::GetInstance().ClearAllTimers();
	return 0;
}


