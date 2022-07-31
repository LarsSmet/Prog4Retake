#include "pch.h"
#include "GunComponent.h"


namespace dae
{
	GunComponent::GunComponent(GameObject* go,/* PhysicsComponent* physicsComp,*/ PlayerComponent* playerComp): BaseComponent{go},/* m_pPhysicsComp{physicsComp},*/ m_pPlayerComp{playerComp}
	{
	}
	GunComponent::~GunComponent()
	{
	}
	void GunComponent::Update(float elapsedSec)
	{
		/*m_pPhysicsComp->GetTransformComp();
		m_pPlayerComp->GetPhysicsComp().*/


		//get player transform component pos
		//set gun transformcomp to this + offset for texture + offset for rotation

		auto playerTransformPos = m_pPlayerComp->GetPhysicsComp()->GetTransformComp()->GetPosition();
		m_Owner->SetPosition(playerTransformPos.x + 10, playerTransformPos.y -3);


		elapsedSec;
	}
	void GunComponent::Shoot()
	{
		//std::make_shared<GameObject>(m_ShootPos.x, m_ShootPos.y);
	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot
	}



}