#include "pch.h"
#include "EnemyComponent.h"
#include <glm/gtx/norm.hpp>


namespace dae
{

	EnemyComponent::EnemyComponent(GameObject* go, PhysicsComponent* physComp, TileMapComponent* tileMap, PlayerComponent* playerComp) : BaseComponent{ go }, m_pPhysicsComponent{ physComp }, m_pTileMapComponent{ tileMap }, m_pPlayerComponent{ playerComp }
	{
		auto enemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });

	}

	EnemyComponent::~EnemyComponent()
	{
	}

	void EnemyComponent::Update(float elapsedSec)
	{

			HandleAI();

	

		m_pPhysicsComponent->Update(elapsedSec);

		auto newEnemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto enemyRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ newEnemyPos.x, newEnemyPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(enemyRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ newEnemyPos.x, newEnemyPos.y });
		}
		else
		{

		}


		//for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		//{

		//	if (m_CellsToCheck[i]->HasCollision())
		//	{
		//		//handle collision
		//		m_pPhysicsComponent->HandleCollision(m_CellsToCheck[i]->GetRectCollider());

		//	}
		//}


	



	}


	void EnemyComponent::HandleAI()
	{
		// TODO: make get cellsize
		//get cells
		auto cellSize = m_CurrentCell->GetSize();
		//cellsize/2 offset to make sure it is in the center, so it always inside the cell, because sometimes it can cause some problems because of the collision

		auto enemyPos = m_CurrentCell->GetPosition();

		auto leftTopCellPos = enemyPos;
		leftTopCellPos.x += (cellSize.x / 2);
		leftTopCellPos.y += (cellSize.y / 2);

		auto rightTopCellPos = enemyPos;
		rightTopCellPos.x += (cellSize.x / 2) + cellSize.x;
		rightTopCellPos.y += (cellSize.y / 2);

		auto leftBotCellPos = enemyPos;
		leftBotCellPos.x += (cellSize.x / 2);
		leftBotCellPos.y += cellSize.y + (cellSize.y / 2);

		auto rightBotCellPos = enemyPos;
		rightBotCellPos.x += (cellSize.x / 2) + cellSize.x;
		rightBotCellPos.y += cellSize.y + (cellSize.y / 2);

		auto leftTopcell = m_pTileMapComponent->GetCell(leftTopCellPos);
		auto rightTopCell = m_pTileMapComponent->GetCell(rightTopCellPos);
		auto leftBotCell = m_pTileMapComponent->GetCell(leftBotCellPos);
		auto rightBotCell = m_pTileMapComponent->GetCell(rightBotCellPos);

		auto playerPos = m_pPlayerComponent->GetPhysicsComp()->GetTransformComp()->GetPosition();

		glm::vec2 playerCenter{ playerPos.x + cellSize.x, playerPos.y + cellSize.y };

		glm::vec2 posToCompare{};


		float closestDistance = FLT_MAX;

		Velocity velocity{};

		std::string finalResult;

		// check dist when player moves 1 cell
		//check top cells
		if (leftTopcell->CanGoUp() && rightTopCell->CanGoUp()) //change current cell with lefttop cell
		{
			posToCompare.x = enemyPos.x + cellSize.x;
			posToCompare.y = enemyPos.y - cellSize.y;
			auto distance = glm::distance2(playerCenter, posToCompare);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				velocity.x = 0;
				velocity.y = -1;
				finalResult = "UP";
			}

		}

		//check bot cells
		if (leftBotCell->CanGoDown() && rightBotCell->CanGoDown())
		{
			posToCompare.x = enemyPos.x + cellSize.x;
			posToCompare.y = enemyPos.y + (3 * cellSize.y);
			auto distance = glm::distance2(playerCenter, posToCompare);


			if (distance < closestDistance)
			{
				closestDistance = distance;
				velocity.x = 0;
				velocity.y = 1;
				finalResult =  "BOT";
			}
		}

		//check left cells

		if (leftTopcell->CanGoLeft() && leftBotCell->CanGoLeft())
		{
			posToCompare.x = enemyPos.x - cellSize.x;
			posToCompare.y = enemyPos.y + cellSize.y;
			auto distance = glm::distance2(playerCenter, posToCompare);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				velocity.x = -1;
				velocity.y = 0;
				finalResult =  "LEFT";
			}
		}
		//check right cells
		if (rightTopCell->CanGoRight() && rightBotCell->CanGoRight())
		{
			posToCompare.x = enemyPos.x + (3 * cellSize.x);
			posToCompare.y = enemyPos.y + cellSize.y;
			auto distance = glm::distance2(playerCenter, posToCompare);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				velocity.x = 1;
				velocity.y = 0;
				finalResult = "RIGHT";
			}

		}

		float speed = 10.0f;

		velocity.x *= speed;
		velocity.y *= speed;
		std::cout << " Final result is: " << finalResult;
		m_pPhysicsComponent->SetVelocity(velocity);
	}

}
