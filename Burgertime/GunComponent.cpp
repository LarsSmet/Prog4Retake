#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>
#include "PhysicsComponent.h"
#include "BulletComponent.h"

namespace dae
{
	GunComponent::GunComponent(GameObject* go,/* PhysicsComponent* physicsComp,*/ PlayerComponent* playerComp, Scene& currentScene): BaseComponent{go},/* m_pPhysicsComp{physicsComp},*/ m_pPlayerComp{playerComp}, m_Scene{ currentScene }
	{
		m_pRenderComp = m_Owner->GetComponent<RenderComponent>();

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

	

		//middle of tank
		m_RotationPos = Point2f{ playerTransformPos.x + 16, playerTransformPos.y + 19 };


		//change this to be based on the gun render pos + offset
		m_ShootPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y -3 };

		m_VectorStartPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y - 3 + 28 };



		m_pRenderComp->SetRotatePoint(Point2f{ 6, 22 });
		RotateGun();
		elapsedSec;
	}
	void GunComponent::Shoot()
	{
		auto bullet = std::make_shared<GameObject>(m_ShootPos.x, m_ShootPos.y);
		RenderComponent* renderComponent = new RenderComponent{ bullet.get(), false , nullptr};
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
	
		//do point - point then put it in a vec and normalize *  speed;

		float xPosVec = m_ShootPos.x - m_VectorStartPos.x;
		float yPosVec = m_ShootPos.y - m_VectorStartPos.y;
		glm::vec2 directionVec{ xPosVec, yPosVec };

		glm::vec2 directionVecNormalized = glm::normalize( directionVec );
		float speed = 50.0f;
		//set velocity based on calculations for direction(normalize) from pos under shoot pos
		bulletComponent->SetVelocity(Velocity{ directionVecNormalized.x * speed, directionVecNormalized.y * speed});


		

	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot

		m_pRenderComp->RotateForward();

	}



}