#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>


namespace dae
{
	GunComponent::GunComponent(GameObject* go,/* PhysicsComponent* physicsComp,*/ PlayerComponent* playerComp, Scene& currentScene): BaseComponent{go},/* m_pPhysicsComp{physicsComp},*/ m_pPlayerComp{playerComp}, m_Scene{ currentScene }
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

		/*shootpos = player + 13
		or
		gunrender +x*/

		//shootpos x + 13



		//middle of tank
		m_RotationPos = Point2f{ playerTransformPos.x + 16, playerTransformPos.y + 19 };



		m_ShootPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y -3 };

		m_VectorStartPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y - 3 + 28 };

	/*	if (test == false)
		{
			Shoot();
		}*/
		elapsedSec;
	}
	void GunComponent::Shoot()
	{
		auto bullet = std::make_shared<GameObject>(m_ShootPos.x, m_ShootPos.y);
		RenderComponent* renderComponent = new RenderComponent{ bullet.get() };
		renderComponent->SetTexture("Bullet.png");
		bullet->AddComponent(renderComponent);
		m_Scene.Add(bullet);
		test = true;

	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot
	}



}