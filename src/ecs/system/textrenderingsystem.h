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
        auto numchars = textcomponent.text.length();
        auto x = transformcomponent.position.GetX() - 2;
        auto y = transformcomponent.position.GetY() + 2;
        auto w = numchars * 6.5f;
        auto h = 12;
        aether::graphics::draw_filled_rectangle(x - 1, y - 1, w + 2, h + 2, c);
        aether::graphics::draw_filled_rectangle(x, y, w, h, aether::graphics::Color(0, 0, 0, c.a));
        font->Print(textcomponent.text.c_str(), transformcomponent.position.GetX(), transformcomponent.position.GetY(), 100, 100, c, true);
    }

};	

