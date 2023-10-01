#pragma once

#include <secs/secs.h>
#include "../components.h"

#include "../../game/assets.h"


class TextRenderingSystem : public secs::EntitySystem
{
public:

    TextRenderingSystem()
    {
        SetStepConfiguration(false, true);
        SetNeededComponents<TransformComponent, TextComponent>();
    }

    void Render( const secs::Entity& e )
	{
        SECS_UNUSED(e);
        auto& transformcomponent = GetComponent<TransformComponent>(e);
        auto& textcomponent = GetComponent<TextComponent>(e);
        auto font = Assets::instance->guiFont;

        aether::graphics::Color c(1.0f, 1.0f, 1.0f, 1.0f);
        if( HasComponent<ColorTintComponent>(e) )
        {
            auto& ctt = GetComponent<ColorTintComponent>(e);
            c = ctt.color;
        }
        font->Print(textcomponent.text.c_str(), transformcomponent.position.GetX(), transformcomponent.position.GetY(), 100, 100, aether::graphics::Color(c.r, c.g, c.b, c.a), true);
    }

};	

