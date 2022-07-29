#include "pch.h"
#include "PlayerComponent.h"
#include "GameObject.h"


namespace dae
{



	PlayerComponent::PlayerComponent(GameObject* go, PhysicsComponent* physComp, TileMapComponent* tileMap): BaseComponent{ go }, m_pPhysicsComponent{ physComp }, m_pTileMapComponent{tileMap}
	{

	}

	PlayerComponent::~PlayerComponent()
	{
	}

	void PlayerComponent::Update(float elapsedSec)
	{
		elapsedSec;

		//handle collision
		//handle move commands

		auto map = m_pTileMapComponent->GetMap();

		for (size_t i = 0; i < map.size(); i++)
		{
			if (map[i].HasCollision())
			{
				m_pPhysicsComponent->HandleCollision(map[i].GetCollider());
			}
		}

	
		m_pPhysicsComponent->Update(elapsedSec);

	}

	void PlayerComponent::SetState(State newState)
	{
		newState;
	}

	State PlayerComponent::GetState()
	{
		return m_State;
	}

}