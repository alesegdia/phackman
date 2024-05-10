#pragma once

#include <secs/secs.h>
#include <aether/aether.h>
#include "../components.h"

#include "../../map/mapscene.h"

#include "../entityfactory.h"

class PlayerInputSystem : public secs::EntitySystem
{
public:

    PlayerInputSystem(MapScene& map_scene, EntityFactory& factory)
        : m_mapScene(map_scene),
          m_factory(factory)
	{
        SetNeededComponents<PlayerInputComponent,
                            AgentInputComponent,
                            TransformComponent>();
	}

    void Process( double delta, const secs::Entity &e ) override
	{
        SECS_UNUSED(delta);

        if( inhibit )
        {
            return;
        }

        auto& agtinput_comp = GetComponent<AgentInputComponent>(e);

        bool u, d, r, l, space;
        u = aether::core::is_key_down( aether::core::KeyCode::Up );
        d = aether::core::is_key_down( aether::core::KeyCode::Down );
        r = aether::core::is_key_down( aether::core::KeyCode::Right );
        l = aether::core::is_key_down( aether::core::KeyCode::Left );
        space = aether::core::is_key_down(aether::core::KeyCode::Space);
        agtinput_comp.requestedDesinfect = aether::core::is_key_down(aether::core::KeyCode::C);
        agtinput_comp.requestedReinforce = aether::core::is_key_just_pressed(aether::core::KeyCode::C);

		bool infect_wants_slow_speed = false;
        if(agtinput_comp.blockInfect == false)
        {
	        if( agtinput_comp.requestedDesinfect)
	        {
	            if (!HasComponent<InfectComponent>(e))
	            {
	                auto& leic = GetEntityProcessor()->AddComponent<InfectComponent>(e);
	                leic.desinfectDuration = 1e6;
	                leic.desinfectTimer = 1e6;
	            }
	            auto& ic = GetEntityProcessor()->GetComponent<InfectComponent>(e);
				ic.desinfect = true;
				infect_wants_slow_speed = true;
	        }
	        else if(HasComponent<InfectComponent>(e))
	        {
	            GetEntityProcessor()->RemoveComponent<InfectComponent>(e);
	            infect_wants_slow_speed = false;
	        }

	        if( agtinput_comp.requestedReinforce )
	        {
	            GetEntityProcessor()->AddComponent<ReinforceComponent>(e);
	        }
		}
		if( u )
		{
			agtinput_comp.requestedFacing = Facing::Up;
		}
		else if( d )
		{
			agtinput_comp.requestedFacing = Facing::Down;
		}

		if( l )
		{
			agtinput_comp.requestedFacing = Facing::Left;
		}
		else if( r )
		{
			agtinput_comp.requestedFacing = Facing::Right;
		}

		agtinput_comp.inputRequested = (u | d | l | r) && !space;
		agtinput_comp.requestedAttack = space;

        auto& tlc = GetComponent<TileComponent>(e);
        auto& tc = GetComponent<TransformComponent>(e);

		if (aether::core::is_key_just_pressed(aether::core::KeyCode::V))
		{
			if (m_mapScene.IsReinforced(tlc.current.GetX(), tlc.current.GetY()))
			{
				GetEntityProcessor()->AddComponent<WallPlacementComponent>(e);
			}
			else
			{
				m_factory.MakeCountdownText(tc.position.GetX(), tc.position.GetY(), "needs power", aether::graphics::Color::Red);
			}
		}

		bool crucible_wants_slow_speed = false;
		if (aether::core::is_key_just_pressed(aether::core::KeyCode::Z))
		{
            auto crucibleEntity = m_mapScene.GetCrucibleEntity();
			auto crucibleTileComponent = GetComponent<TileComponent>(crucibleEntity);

			if (crucibleTileComponent.current == tlc.current)
			{
				DestroyEntity(crucibleEntity);
				agtinput_comp.carryCrucible = true;

				auto& shootComponent = GetComponent<ShootComponent>(e);
				shootComponent.force_disable = true;
				auto& infectComponent = GetComponent<InfectComponent>(e);
                agtinput_comp.blockInfect = true;

                for(auto spawner : GetEntityProcessor()->GetAllEntitiesWithTag("spawner"))
                {
	                auto& spawnerComponent = GetComponent<SpawnComponent>(spawner);
                    spawnerComponent.maxNumEntities = 20;

                    auto& spawnerShootComponent = GetComponent<ShootComponent>(spawner);
                    spawnerShootComponent.rate = 0.5e6;
                }

			}
		}

		crucible_wants_slow_speed = agtinput_comp.carryCrucible;


		if (m_mapScene.IsInfected(tlc.current.GetX(), tlc.current.GetY()))
		{
			if(crucible_wants_slow_speed)
			{
				agtinput_comp.speed = agtinput_comp.lowest_speed;
			}
			else
			{
				agtinput_comp.speed = agtinput_comp.low_speed;
			}
		}
		else if(m_mapScene.IsReinforced(tlc.current.GetX(), tlc.current.GetY()))
		{
			agtinput_comp.speed = agtinput_comp.fast_speed;
			if(crucible_wants_slow_speed)
			{
				agtinput_comp.speed = agtinput_comp.normallow_speed;
			}
		}
		else
		{
			if(crucible_wants_slow_speed || infect_wants_slow_speed)
			{
				agtinput_comp.speed = agtinput_comp.low_speed;
			}
			else
			{
				agtinput_comp.speed = agtinput_comp.normal_speed;
			}
		}


	}

    bool inhibit = false;


private:
    MapScene& m_mapScene;
    EntityFactory& m_factory;


};
