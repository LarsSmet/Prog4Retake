#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>
#include "PhysicsComponent.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"

namespace dae
{
	GunComponent::GunComponent(GameObject* go, PlayerComponent* playerComp, EnemyComponent* enemyComp, Scene& currentScene, TileMapComponent* tileMap): 
		BaseComponent{ go }, m_pPlayerComp{ playerComp }, m_pEnemyComp{ enemyComp }, m_Scene{ currentScene }, m_pTileMap{ tileMap }, 
		m_CurrentCooldown{0}, m_MaxCooldown{2}, m_OnCooldown{false}/*, m_GunOwner{GunOwner::enemy}*/
	{
		m_pRenderComp = m_Owner->GetComponent<RenderComponent>();
		
		if (m_pPlayerComp != nullptr)
		{
			std::cout << "Is owned by player";
			m_GunOwner = GunOwner::player;
		}
		else if (m_pEnemyComp != nullptr)
		{
			std::cout << "Is owned by enemy";
			m_GunOwner = GunOwner::enemy;
		}
		

	}
	GunComponent::~GunComponent()
	{
	}
	void GunComponent::Update(float elapsedSec)
	{
		if (m_OnCooldown && m_CurrentCooldown <= 0 )
		{
			m_OnCooldown = false;
			
		}
		else if(m_OnCooldown && m_CurrentCooldown > 0)
		{
			m_CurrentCooldown -= elapsedSec;
		}
		

		//if not enemy
		if (m_GunOwner == GunOwner::player) //TODO: in move replace playerphys comp to enemy comp when cowner is enemy
		{
			Move();
			RotateGun();
		//	Shoot();
		}
	
		elapsedSec;
	}

	void GunComponent::Move()
	{
		glm::vec2 ownerTransformPos;

		if (m_GunOwner == GunOwner::player)
		{
			ownerTransformPos = m_pPlayerComp->GetPhysicsComp()->GetTransformComp()->GetPosition();
		}
		else if (m_GunOwner == GunOwner::enemy)
		{
			ownerTransformPos = m_pEnemyComp->GetPhysicsComp()->GetTransformComp()->GetPosition();
		}
		/*auto playerTransformPos = m_pPlayerComp->GetPhysicsComp()->GetTransformComp()->GetPosition();*/
		m_Owner->SetPosition(ownerTransformPos.x + 10, ownerTransformPos.y - 3);

		//middle of tank
		m_RotationPos = Point2f{ ownerTransformPos.x + 16, ownerTransformPos.y + 19 };
		m_pRenderComp->SetRotatePoint(Point2f{ 6, 22 });

	}


	void GunComponent::Shoot()
	{
		if (m_OnCooldown)
		{
			
		}
		else
		{
			m_CurrentCooldown = m_MaxCooldown;
			m_OnCooldown = true;



			//do direction
			float degreeOffset = -90;
			auto radians = glm::radians(float(m_pRenderComp->GetAngle()) + degreeOffset);
			float directionX = glm::cos(radians);
			float directionY = glm::sin(radians);



			glm::vec2 directionVec{ directionX, directionY };


			auto absoluteVecX = glm::abs(directionVec.x);
			auto absoluteVecY = glm::abs(directionVec.y);



			//because of -90 x and y are swapped for absolute vec
			float offSetX = -3;
			float offSetY = 19;

			Point2f shootPos;
			shootPos.x = m_RotationPos.x + offSetX * absoluteVecY + offSetY * directionX;
			shootPos.y = m_RotationPos.y + offSetX * absoluteVecX + offSetY * directionY;



			auto bullet = std::make_shared<GameObject>(shootPos.x, shootPos.y);
			RenderComponent* renderComponent = new RenderComponent{ bullet.get(), false , nullptr };
			renderComponent->SetTexture("Bullet.png");
			bullet->AddComponent(renderComponent);

			auto texture = renderComponent->GetTexture()->GetSDLTexture();
			SDL_Point size;
			SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
			Rectf bulletShape{ shootPos.x,shootPos.y + float(size.y), float(size.x),float(size.y) };
			RectColliderComponent* bulletCollider = new RectColliderComponent{ bullet.get(), bulletShape };
			PhysicsComponent* physicsComp = new PhysicsComponent{ bullet.get(), bullet->GetTransformComp(), bulletCollider };
			bullet->AddComponent(physicsComp);
			std::cout << "Gunowner is : " << int(m_GunOwner);

			BulletComponent* bulletComponent = new BulletComponent{ bullet.get(), physicsComp, m_pTileMap, m_GunOwner };
			float speed = 150.0f;
			//set velocity based on calculations for direction from pos under shoot pos
			bulletComponent->SetVelocity(Velocity{ directionVec.x * speed, directionVec.y * speed });
			bullet->AddComponent(bulletComponent);
			m_Scene.LateAdd(bullet);


			
			//Point2f shootPos2;
			//shootPos2.x = m_RotationPos.x + offSetX * absoluteVecY + offSetY * directionX;
			//shootPos2.y = m_RotationPos.y + offSetX * absoluteVecX + offSetY * directionY;



			//auto bullet2 = std::make_shared<GameObject>(shootPos2.x, shootPos2.y);
			//RenderComponent* render2Component = new RenderComponent{ bullet2.get(), false , nullptr };
			//render2Component->SetTexture("Bullet.png");
			//bullet2->AddComponent(render2Component);

			//auto texture2 = render2Component->GetTexture()->GetSDLTexture();
			//SDL_Point size2;
			//SDL_QueryTexture(texture2, nullptr, nullptr, &size2.x, &size2.y);
			//Rectf bulletShape2{ shootPos2.x,shootPos2.y + float(size2.y), float(size2.x),float(size2.y) };
			//RectColliderComponent* bullet2Collider = new RectColliderComponent{ bullet2.get(), bulletShape2 };
			//PhysicsComponent* physics2Comp = new PhysicsComponent{ bullet2.get(), bullet2->GetTransformComp(), bullet2Collider };
			//bullet2->AddComponent(physics2Comp);
			//std::cout << "Gunowner is : " << int(m_GunOwner);

			//BulletComponent* bullet2Component = new BulletComponent{ bullet2.get(), physics2Comp, m_pTileMap, m_GunOwner };
			//float speed2 = 150.0f;
			////set velocity based on calculations for direction from pos under shoot pos
			//bullet2Component->SetVelocity(Velocity{ directionVec.x * speed2, directionVec.y * speed2 });
			//bullet2->AddComponent(bullet2Component);
			//m_Scene.Add(bullet2);

			//if (bullet2 == nullptr)
			//{
			//	std::cout << "why is this null";
			//}

		}
		


	}
	void GunComponent::RotateGun()
	{
		//calc offset for rot


		
		m_pRenderComp->RotateForward();

	}



}