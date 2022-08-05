#include "pch.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

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


		m_pPhysicsComponent->Update(elapsedSec);

		//handle collision
		//handle move commands

		auto map = m_pTileMapComponent->GetCollisionMap();

		for (size_t i = 0; i < map.size(); i++)
		{
			/*if (map[i].HasCollision())
			{*/
				//add if cell is teleporter

				//std::cout << "called before handlecol func";

				if (map[i].GetCellType() == CellType::teleport)
				{
					auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

					float offset = 32; //has to be changed later

					Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


			/*		if (utils::IsOverlapping(rect, map[i].GetCollider().get()->GetRectCollider()))
					{

						Teleport();

					}*/

					if (utils::IsOverlapping(rect, map[i].GetRectCollider())) //still chage
					{

						Teleport();

					}

				}
				else
				{

					m_pPhysicsComponent->HandleCollision(map[i].GetCollider().get());
				}
			//}
		}

	
		//m_pPhysicsComponent->Update(elapsedSec);

	}

	void PlayerComponent::SetState(State newState)
	{
		newState;
	}

	State PlayerComponent::GetState()
	{
		return m_State;
	}
	PhysicsComponent* PlayerComponent::GetPhysicsComp()
	{
		return m_pPhysicsComponent;
	}

	void PlayerComponent::Teleport()
	{

		auto spawnMap = m_pTileMapComponent->GetSpawnMap();

		size_t mapSize = spawnMap.size();

		//random number
		int randomCell = rand() % mapSize;

		//do teleport

		auto posToTeleportTo = spawnMap[randomCell].GetCollider()->GetPosition();

		m_pPhysicsComponent->GetColliderComponent()->SetPosition(posToTeleportTo.x, posToTeleportTo.y);
		m_pPhysicsComponent->GetTransformComp()->SetPosition(posToTeleportTo.x, posToTeleportTo.y);

	}


}