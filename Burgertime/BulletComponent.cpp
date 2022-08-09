#include "pch.h"
#include "BulletComponent.h"


namespace dae
{
	BulletComponent::BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap) : BaseComponent{ go }, m_pPhysicsComponent{ physicsComp }, m_pTileMapComponent{ tileMap }
	{
		m_BounceCounter = 0;
	}
	BulletComponent::~BulletComponent()
	{

	}

	void BulletComponent::Update(float elapsedSec)
	{
		elapsedSec;
		HandleBounce();

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
						std::cout << "KILL";
						m_Owner->~GameObject();
					}
				
			}
		}



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