#include "pch.h"
#include "BulletComponent.h"
#include "EntityManager.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EntityManager.h"


namespace dae
{
	BulletComponent::BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap, GunOwner gunOwner) : BaseComponent{ go },
		m_pPhysicsComponent{ physicsComp }, m_pTileMapComponent{ tileMap }, m_GunOwner{gunOwner}, m_EnemiesAreChecked{false}
	{

	
		m_pPhysicsComponent->SetVelocity(m_Velocity);
		m_BounceCounter = 0;
		auto bulletPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ bulletPos.x, bulletPos.y });

		CheckCurrentEnemies();


	}
	BulletComponent::~BulletComponent()
	{
		//std::cout << "DELEEEEEEEEEEEEEETE";
	}

	void BulletComponent::Update(float elapsedSec)
	{
		elapsedSec;

		if (m_EnemiesAreChecked)
		{
			CheckCurrentEnemies();
		}

		HandleDamage();
		HandleBounce();
	
		
			//error not because bullet gets deleted
		

		//do movement
		//m_pPhysicsComp->SetVelocity()
	}

	void BulletComponent::SetVelocity(Velocity velocity)
	{
		
		m_Velocity = velocity;
		std::cout << m_Velocity.y << '\n';
		m_pPhysicsComponent->SetVelocity(m_Velocity);
	}

	void BulletComponent::SetEnemiesAreChecked(bool check)
	{
		m_EnemiesAreChecked = check;


	}

	

	void BulletComponent::HandleBounce()
	{
		//std::cout << "handlebounce";

		auto bulletPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto bulletRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		//std::cout << bulletRectCol.bottom << '\n';
		

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ bulletPos.x, bulletPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(bulletRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ bulletPos.x, bulletPos.y });
			
		}

		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{
			
			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				
				

				Velocity velocityAfterBounce = m_Velocity;
							
				//check if top hit or bot hit
				//get hitinfo from hit, check which side is hit then adjust velocity accordingly
				

				auto info = m_pPhysicsComponent->GetColliderComponent()->OnCollision(m_CellsToCheck[i]->GetRectCollider());
				
				if (!info.hit)
				{
					
					continue;
				}
				
				if (info.topColLeftIsHit || info.topColRightIsHit)
				{
					if (m_Velocity.y < 0)
					{
						velocityAfterBounce.y *= -1;
						++m_BounceCounter;

						//TODO: do breka to stop cells counting for multiple bounces
					}
				}
				else if (info.botColLeftIsHit || info.botColRightIsHit)
				{
					if (m_Velocity.y > 0)
					{
						velocityAfterBounce.y *= -1;
						++m_BounceCounter;

					}
				}
				else if (info.leftColBotIsHit || info.leftColTopIsHit)
				{
					if (m_Velocity.x < 0)
					{
						velocityAfterBounce.x *= -1;
						++m_BounceCounter;
					}
					}
				else if (info.rightColBotIsHit || info.rightColTopIsHit)
				{
					if (m_Velocity.x > 0)
					{
						velocityAfterBounce.x *= -1;
						++m_BounceCounter;
					}
				}

				SetVelocity(velocityAfterBounce);
			
						
						

			
					if (m_BounceCounter >= 6) //after 5th bounce, if hits wall dont bounce but kill
					{
						//std::cout << "KILL";
						
					//	std::cout << "BOUNCECOUNTER: " << m_BounceCounter << '\n';
						KillBullet();
					}
				
			}
		}



	}

	void BulletComponent::HandleDamage()
	{
		if (m_GunOwner == GunOwner::player)
		{

			//buauto enemies = EntityManager::GetInstance().GetEnemies();

			//std::cout << " There are currently: " << enemies.size() << " enemies ";

			for (size_t i = 0; i < m_EnemyComponents.size(); ++i)
			{
				auto rectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
				float offset = -32; //has to be changed later

				Rectf rect{ rectCol.left, rectCol.bottom - offset, rectCol.width, rectCol.height };


				auto enemyComp = m_EnemyComponents[i];

				if (enemyComp == nullptr)
				{
					//std::cout << "mistake";
				}
				else
				{
					//	std::cout << "no mistake";

					std::cout << " SCENE BEFORE ERROR: " << SceneManager::GetInstance().GetCurrentSceneIndex();

					if (utils::IsOverlapping(rect, enemyComp->GetPhysicsComp()->GetColliderComponent()->GetRectCollider())) //still chage
					{
						//std::cout << "POG";
						

						
						m_EnemyComponents[i]->DealDamage(1);
						KillBullet();

						
						
						//SceneManager::GetInstance().GoToNextScene();

						
						

					}

				}


			}


		}


		//if (utils::IsOverlapping(rect, m_CellsToCheck[i]->GetRectCollider())) //still chage
		//{

		//	

		//}

		
	}

	

	void BulletComponent::KillBullet()
	{
		m_Owner->Destroy();
		
	}

	
	void BulletComponent::CheckCurrentEnemies()
	{
		m_PlayerComponents.clear();
		m_EnemyComponents.clear();

		auto players = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("PLAYER");
		auto enemies = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("ENEMY");

		for (auto player : players)
		{
			auto playerComp = player->GetComponent<PlayerComponent>();
			if (playerComp != nullptr)
			{
				m_PlayerComponents.emplace_back(playerComp);

			}
		}

		for (auto enemy : enemies)
		{
			auto enemyComp = enemy->GetComponent<EnemyComponent>();
			if (enemyComp != nullptr)
			{
				m_EnemyComponents.emplace_back(enemyComp);

			}
		}


		m_EnemiesAreChecked = true;

	}

}