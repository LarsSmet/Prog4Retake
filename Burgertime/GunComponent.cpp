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
		//m_ShootPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y -3 };



		//m_VectorStartPos = Point2f{ playerTransformPos.x + 13, playerTransformPos.y - 3 + 28 };

		//std::cout << m_Owner->GetTransformComp()->GetPosition().x << "   }";

		m_pRenderComp->SetRotatePoint(Point2f{ 6, 22 });
		RotateGun();
		elapsedSec;
	}
	void GunComponent::Shoot()
	{


		//do direction
		float degreeOffset = -90;
		auto radians = glm::radians(float(m_pRenderComp->GetAngle()) + degreeOffset);
		float directionX = glm::cos(radians);
		float directionY = glm::sin(radians);



		glm::vec2 directionVec{ directionX, directionY };
		std::cout << " direction x: " << directionX;
		



		auto absoluteVecX = glm::abs(directionVec.x);
		auto absoluteVecY = glm::abs(directionVec.y);
	


		//because of -90 x and y are swapped for absolute vec
		float offSetX = -3;
		float offSetY = 19;

		Point2f shootPos;
		shootPos.x = m_RotationPos.x + offSetX * absoluteVecY  + offSetY * directionX;
		shootPos.y = m_RotationPos.y  + offSetX * absoluteVecX + offSetY * directionY;



		auto bullet = std::make_shared<GameObject>(shootPos.x, shootPos.y);
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
	



;
		float speed = 150.0f;
		//set velocity based on calculations for direction from pos under shoot pos
		bulletComponent->SetVelocity(Velocity{ directionVec.x * speed, directionVec.y * speed});


		

	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot


		
		m_pRenderComp->RotateForward();

	}



}