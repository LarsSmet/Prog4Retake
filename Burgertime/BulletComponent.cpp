#include "pch.h"
#include "BulletComponent.h"


namespace dae
{
	BulletComponent::BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap) : BaseComponent{ go }, m_pPhysicsComp{ physicsComp }, m_pTileMapComp{ tileMap }
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
		m_pPhysicsComp->SetVelocity(m_Velocity);
	}

	void BulletComponent::HandleBounce()
	{
		auto colMap = m_pTileMapComp->GetCollisionMap();

		for (size_t i = 0; i < colMap.size(); i++)
		{
			
				Velocity velocityAfterBounce = m_Velocity;
				
				//check if top hit or bot hit
				//get hitinfo from hit, check which side is hit then adjust velocity accordingly
			

				auto info = m_pPhysicsComp->GetColliderComponent()->OnCollision((colMap[i]->GetRectCollider()));
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
			
			

		}
		if (m_BounceCounter >= 4)
		{
			std::cout << "KILL";
			m_Owner->~GameObject();
		}
		
	

	}

}