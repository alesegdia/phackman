#pragma once

#include <secs/secs.h>
#include "../components.h"

#include "../../game/assets.h"

#include <allegro5/allegro_ttf.h>

class TextRenderingSystem : public secs::EntitySystem
{
public:

    TextRenderingSystem()
    {
        setStepConfiguration(false, true);
        setNeededComponents<TransformComponent, TextComponent>();
    }

    void render( const secs::Entity& e )
	{
        SECS_UNUSED(e);
        auto& transformcomponent = component<TransformComponent>(e);
        auto& textcomponent = component<TextComponent>(e);
        auto font = Assets::instance->guiFont;

        ALLEGRO_COLOR c = al_map_rgba(255, 255, 255, 255);
        if( hasComponent<ColorTintComponent>(e) )
        {
            auto& ctt = component<ColorTintComponent>(e);
            c = ctt.color;
        }
        font.print(textcomponent.text.c_str(), transformcomponent.position.x(), transformcomponent.position.y(), 100, 100, aether::graphics::Color(c.r, c.g, c.b, c.a), true);
    }

};	

