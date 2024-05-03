#pragma once

#include <secs/secs.h>
#include "../components.h"

class FadingSystem : public secs::TypedEntitySystem<FadeComponent, ColorTintComponent>
{
public:
    void process( double delta, const secs::Entity& e, FadeComponent& fadecomponent, ColorTintComponent& colortintcomponent )
	{
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        float alpha = fadecomponent.currentAlpha;
        if( alpha > 0 )
        {
            alpha -= fadecomponent.rate;
            if( alpha <= 0 )
            {
                alpha = 0;
            }
            auto c = colortintcomponent.color;
            colortintcomponent.color = aether::graphics::Color(c.r / 255.f, c.g / 255.f, c.b / 255.f, alpha);
            fadecomponent.currentAlpha = alpha;
        }
	}
};	

