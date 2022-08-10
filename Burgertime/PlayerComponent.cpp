#include "pch.h"
#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace dae
{



	PlayerComponent::PlayerComponent(GameObject* go, PhysicsComponent* physComp, TileMapComponent* tileMap): BaseComponent{ go }, m_pPhysicsComponent{ physComp }, m_pTileMapComponent{tileMap}
	{
		auto playerPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y});
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

		//auto map = m_pTileMapComponent->GetCollisionMap();
		/*std::cout << map.size();*/
		
		//m_pTileMapComponent->GetCell(Point2f{16,450});


		auto playerPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto playerRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		
		//offset needed to make sure it is in the cell, because sometimes the collision would make it so that it would be in another cell
		float offSet = 5;
		playerPos.x += offSet;
		playerPos.y += offSet;

		//std::cout << " x value: " << playerPos.x << " y value: " << playerPos.y;

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ playerPos.x, playerPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(playerRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ playerPos.x, playerPos.y });
		}
		else
		{
			//std::cout << " Can go left is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoLeft();
			//std::cout << /*" Can go right is: " <<*/ m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoRight();
			//std::cout << " Can go up is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoUp();
			//std::cout << " Can go down is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoDown();
		}
		

		//if old cell is not new cell, update

		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{
			//std::cout << "SIZE OF CELL VEC " << m_CellsToCheck.size();
			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				if (m_CellsToCheck[i]->GetCellType() == CellType::teleport)
				{
					auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

					float offset = 32; //has to be changed later

					Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


					if (utils::IsOverlapping(rect, m_CellsToCheck[i]->GetRectCollider())) //still chage
					{

						Teleport();

					}

				}
				else
				{

					m_pPhysicsComponent->HandleCollision(m_CellsToCheck[i]->GetRectCollider());
				}
			}
		}


		//for (size_t i = 0; i < map.size(); i++)
		//{
		//	/*if (map[i].HasCollision())
		//	{*/
		//		//add if cell is teleporter

		//		//std::cout << "called before handlecol func";

		//		if (map[i]->GetCellType() == CellType::teleport)
		//		{
		//			auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

		//			float offset = 32; //has to be changed later

		//			Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


		//	/*		if (utils::IsOverlapping(rect, map[i].GetCollider().get()->GetRectCollider()))
		//			{

		//				Teleport();

		//			}*/

		//			if (utils::IsOverlapping(rect, map[i]->GetRectCollider())) //still chage
		//			{

		//				Teleport();

		//			}

		//		}
		//		else
		//		{

		//			m_pPhysicsComponent->HandleCollision(map[i]->GetRectCollider());
		//		}
		//	//}
		//}

	
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

	/*	auto posToTeleportTo = spawnMap[randomCell]->GetCollider()->GetPosition();*/
		auto posToTeleportTo = spawnMap[randomCell]->GetPosition();

		m_pPhysicsComponent->GetColliderComponent()->SetPosition(posToTeleportTo.x, posToTeleportTo.y);
		m_pPhysicsComponent->GetTransformComp()->SetPosition(posToTeleportTo.x, posToTeleportTo.y);

	}


}