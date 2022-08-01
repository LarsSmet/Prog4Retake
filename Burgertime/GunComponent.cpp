#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>
#include "PhysicsComponent.h"
#include "BulletComponent.h"

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


		elapsedSec;
	}
	void GunComponent::Shoot()
	{
		auto bullet = std::make_shared<GameObject>(m_ShootPos.x, m_ShootPos.y);
		RenderComponent* renderComponent = new RenderComponent{ bullet.get() };
		renderComponent->SetTexture("Bullet.png");
		bullet->AddComponent(renderComponent);

		auto texture = renderComponent->GetTexture()->GetSDLTexture();
		SDL_Point size;
		SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
		Rectf bulletShape{ m_ShootPos.x,m_ShootPos.y + float(size.y), float(size.x),float(size.y) };
		RectColliderComponent* bulletCollider = new RectColliderComponent{ bullet.get(), bulletShape };
		PhysicsComponent* physicsComp = new PhysicsComponent{ bullet.get(), bullet->GetTransformComp(), bulletCollider };
		bullet->AddComponent(physicsComp);
		BulletComponent* bulletComponent = new BulletComponent{ bullet.get(), physicsComp };
		bullet->AddComponent(bulletComponent);
		m_Scene.Add(bullet);
	
		bulletComponent->SetVelocity(Velocity{50.0f, 50.0f});

	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot
	}



}