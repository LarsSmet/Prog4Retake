#include "pch.h"
#include "GunComponent.h"
#include <RenderComponent.h>
#include "PhysicsComponent.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"

namespace dae
{
	GunComponent::GunComponent(GameObject* go, PlayerComponent* playerComp, EnemyComponent* enemyComp, Scene& currentScene, TileMapComponent* tileMap): 
		BaseComponent{ go }, m_pPlayerComp{ playerComp }, m_pEnemyComp{ enemyComp }, m_Scene{ currentScene }, m_pTileMap{ tileMap }
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
		//if not enemy
		if (m_GunOwner == GunOwner::player) //TODO: in move replace playerphys comp to enemy comp when cowner is enemy
		{
			Move();
			RotateGun();
		}
		//if (m_OwnedByPlayer)
		//{
		//	Move();
		//	RotateGun();
		//}
		//else
		//{
		//	//do state thingy from ENEMY
		//}
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
		shootPos.x = m_RotationPos.x + offSetX * absoluteVecY  + offSetY * directionX;
		shootPos.y = m_RotationPos.y  + offSetX * absoluteVecX + offSetY * directionY;



		auto bullet = std::make_shared<GameObject>(shootPos.x, shootPos.y);
		RenderComponent* renderComponent = new RenderComponent{ bullet.get(), false , nullptr};
		renderComponent->SetTexture("Bullet.png");
		bullet->AddComponent(renderComponent);

		auto texture = renderComponent->GetTexture()->GetSDLTexture();
		SDL_Point size;
		SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
		Rectf bulletShape{ shootPos.x,shootPos.y + float(size.y), float(size.x),float(size.y) };
		RectColliderComponent* bulletCollider = new RectColliderComponent{ bullet.get(), bulletShape };
		PhysicsComponent* physicsComp = new PhysicsComponent{ bullet.get(), bullet->GetTransformComp(), bulletCollider };
		bullet->AddComponent(physicsComp);
		BulletComponent* bulletComponent = new BulletComponent{ bullet.get(), physicsComp, m_pTileMap };
		bullet->AddComponent(bulletComponent);
		m_Scene.Add(bullet);
	

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