#include "pch.h"
#include "BulletComponent.h"


namespace dae
{
	BulletComponent::BulletComponent(GameObject* go,  PhysicsComponent* physicsComp): BaseComponent{go}, m_pPhysicsComp{physicsComp}
	{

	}
	BulletComponent::~BulletComponent()
	{

	}

	void BulletComponent::Update(float elapsedSec)
	{
		elapsedSec;
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
		
	}

}