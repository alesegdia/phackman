#pragma once

#include <secs/secs.h>
#include "../components.h"
#include "../../map/mapscene.h"
#include "../entityfactory.h"

class PoweringSystem : public secs::TypedEntitySystem<PowerConsumerComponent, TileComponent>
{
public:

    PoweringSystem(MapScene& map_scene, EntityFactory& factory)
        : m_mapScene(map_scene), m_factory(factory)
    {

    }

    void process( double delta, const secs::Entity& e, PowerConsumerComponent& powerconsumercomponent, TileComponent& tilecomponent ) override
    {
        SECS_UNUSED(delta);
        SECS_UNUSED(e);
        powerconsumercomponent.powered =
                m_mapScene.isReinforced(
                    tilecomponent.current.GetX(),
                    tilecomponent.current.GetY());
	}

private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;

};	

