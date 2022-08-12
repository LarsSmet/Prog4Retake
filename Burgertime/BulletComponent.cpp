#include "pch.h"
#include "BulletComponent.h"
#include "EntityManager.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"

namespace dae
{
	BulletComponent::BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap) : BaseComponent{ go }, m_pPhysicsComponent{ physicsComp }, m_pTileMapComponent{ tileMap }, m_KillBullet{false}
	{
		m_BounceCounter = 0;
	}
	BulletComponent::~BulletComponent()
	{
		//std::cout << "DELEEEEEEEEEEEEEETE";
	}

	void BulletComponent::Update(float elapsedSec)
	{
		elapsedSec;
		HandleDamage();
		HandleBounce();
	
		if (m_KillBullet)
		{
			KillBullet();
		}

		//do movement
		//m_pPhysicsComp->SetVelocity()
	}

	void BulletComponent::SetVelocity(Velocity velocity)
	{
		m_Velocity = velocity;
		m_pPhysicsComponent->SetVelocity(m_Velocity);
	}

	void BulletComponent::HandleBounce()
	{


		auto bulletPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto bulletRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ bulletPos.x, bulletPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(bulletRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ bulletPos.x, bulletPos.y });
		}

		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{
			
			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				
				

				Velocity velocityAfterBounce = m_Velocity;
							
				//check if top hit or bot hit
				//get hitinfo from hit, check which side is hit then adjust velocity accordingly
				

				auto info = m_pPhysicsComponent->GetColliderComponent()->OnCollision(m_CellsToCheck[i]->GetRectCollider());
				
				if (!info.hit)
				{
					
					continue;
				}
				
				if (info.topColLeftIsHit || info.topColRightIsHit)
				{
					velocityAfterBounce.y *= -1;
				}
				else if (info.botColLeftIsHit || info.botColRightIsHit)
				{
					velocityAfterBounce.y *= -1;
				}
				else if (info.leftColBotIsHit || info.leftColTopIsHit)
				{
					velocityAfterBounce.x *= -1;
				}
				else if (info.rightColBotIsHit || info.rightColTopIsHit)
				{
					velocityAfterBounce.x *= -1;
				}

				SetVelocity(velocityAfterBounce);
				++m_BounceCounter;
						
						

					
					if (m_BounceCounter >= 4)
					{
						//std::cout << "KILL";
						
						m_KillBullet = true;
					}
				
			}
		}



	}

	void BulletComponent::HandleDamage()
	{

		auto enemies = EntityManager::GetInstance().GetEnemies();

		std::cout << " There are currently: " << enemies.size() << " enemies ";

		for (size_t i = 0; i < enemies.size(); ++i)
		{
			auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
			float offset =  - 32; //has to be changed later

			Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


			auto enemyComp = enemies[i]->GetComponent<EnemyComponent>();
			
			if (enemyComp == nullptr)
			{
				std::cout << "mistake";
			}
			else
			{
				std::cout << "no mistake";

				if (utils::IsOverlapping(rect, enemyComp->GetPhysicsComp()->GetColliderComponent()->GetRectCollider())) //still chage
				{
					std::cout << "POG";
					m_KillBullet = true;
					enemies[i]->~GameObject();
					//also delete it from vec.

				}

			}
			
			
		}

	
		


		//if (utils::IsOverlapping(rect, m_CellsToCheck[i]->GetRectCollider())) //still chage
		//{

		//	

		//}

		
	}

	void BulletComponent::KillBullet()
	{
		m_Owner->~GameObject();
	}

	//void BulletComponent::HandleBounce()
	//{
	//	auto colMap = m_pTileMapComp->GetCollisionMap();

	//	for (size_t i = 0; i < colMap.size(); i++)
	//	{
	//		
	//			Velocity velocityAfterBounce = m_Velocity;
	//			
	//			//check if top hit or bot hit
	//			//get hitinfo from hit, check which side is hit then adjust velocity accordingly
	//		

	//			auto info = m_pPhysicsComp->GetColliderComponent()->OnCollision((colMap[i]->GetRectCollider()));
	//			if (!info.hit)
	//			{
	//				
	//				continue;
	//			}
	//	
	//			if (info.topColLeftIsHit || info.topColRightIsHit)
	//			{
	//				velocityAfterBounce.y *= -1;
	//			}
	//			else if (info.botColLeftIsHit || info.botColRightIsHit)
	//			{
	//				velocityAfterBounce.y *= -1;
	//			}
	//			else if (info.leftColBotIsHit || info.leftColTopIsHit)
	//			{
	//				velocityAfterBounce.x *= -1;
	//			}
	//			else if (info.rightColBotIsHit || info.rightColTopIsHit)
	//			{
	//				velocityAfterBounce.x *= -1;
	//			}

	//			SetVelocity(velocityAfterBounce);
	//			++m_BounceCounter;
	//		
	//		

	//	}
	//	if (m_BounceCounter >= 4)
	//	{
	//		std::cout << "KILL";
	//		m_Owner->~GameObject();
	//	}
	//	
	//

	//}

}