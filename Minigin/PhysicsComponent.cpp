#include "MiniginPCH.h"
#include "PhysicsComponent.h"

namespace dae
{

	PhysicsComponent::PhysicsComponent(GameObject* go, TransformComponent* transformComp, RectColliderComponent* colliderComp) : BaseComponent{ go }, m_pTransformComp{ transformComp }, m_pColliderComp{ colliderComp }, m_Velocity{ 0,0 }
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{
	/*	delete m_pTransformComp;
		m_pTransformComp = nullptr;*/

		delete m_pColliderComp;
		m_pColliderComp = nullptr;

	
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		//move transform(go with visual) and collider(collision) depending on the velocity
		
		

		m_pTransformComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);
		m_pColliderComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);

		//std::cout << "coliderPos: " << m_pColliderComp->GetPosition().y;

	}



	RectColliderComponent* PhysicsComponent::GetColliderComponent()
	{
		return m_pColliderComp;
	}

	void PhysicsComponent::SetVelocity(Velocity velocity)
	{
		m_Velocity = velocity;
	}

	void PhysicsComponent::SetXVelocity(float xVelocity)
	{
		m_Velocity.x = xVelocity;
	}

	void PhysicsComponent::SetYVelocity(float yVelocity)
	{
		m_Velocity.y = yVelocity;
	}

	Velocity PhysicsComponent::GetVelocity()
	{
		return m_Velocity;
	}

	void PhysicsComponent::HandleCollision(RectColliderComponent* collision)
	{
		//TODO: when landing vertically it also uses the horizontal movement causing the player to tp to the side of the cell. 
		//OR  -> left and right side get triggered by the raycast, causing these teleporting movements

		auto colInfo = m_pColliderComp->OnCollision(collision);

		if (colInfo.leftColBotIsHit) 
		{
			auto hitPoint = colInfo.leftColBot.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x + 1);
			m_pColliderComp->SetXPosition(hitPoint.x + 1);
		
		}
		else if (colInfo.leftColTopIsHit)
		{
			auto hitPoint = colInfo.leftColTop.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x + 1);
			m_pColliderComp->SetXPosition(hitPoint.x + 1);

		}
		else if (colInfo.rightColBotIsHit)
		{
			auto hitPoint = colInfo.rightColBot.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width - 1);
			m_pColliderComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width - 1);

		}
		else if (colInfo.rightColTopIsHit)
		{
			auto hitPoint = colInfo.rightColTop.intersectPoint;

			m_pTransformComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width - 1);
			m_pColliderComp->SetXPosition(hitPoint.x - m_pColliderComp->GetRectCollider().width - 1);
		}

		//vertical
		if (colInfo.botColLeftIsHit)
		{
			auto hitPoint = colInfo.botColLeft.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y - m_pColliderComp->GetRectCollider().height -1);
			m_pColliderComp->SetYPosition(hitPoint.y -1);

		}
		else if (colInfo.botColRightIsHit)
		{
			auto hitPoint = colInfo.botColRight.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y - m_pColliderComp->GetRectCollider().height - 1);
			m_pColliderComp->SetYPosition(hitPoint.y - 1);
		}
		else if (colInfo.topColLeftIsHit)
		{
			auto hitPoint = colInfo.topColLeft.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y + 1);
			m_pColliderComp->SetYPosition(hitPoint.y + m_pColliderComp->GetRectCollider().height +1);
		}
		else if (colInfo.topColRightIsHit)
		{
			auto hitPoint = colInfo.topColRight.intersectPoint;

			m_pTransformComp->SetYPosition(hitPoint.y + 1);
			m_pColliderComp->SetYPosition(hitPoint.y + m_pColliderComp->GetRectCollider().height + 1);
		}


	}

}