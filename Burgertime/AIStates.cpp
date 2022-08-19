#include "pch.h"
#include "AIStates.h"
#include "EnemyComponent.h"
#include "GunComponent.h"
#include <glm/gtx/norm.hpp>

namespace dae
{
	//Move state

	MoveState::MoveState(PlayerComponent* playerComp) : AIState{ playerComp }
	{

	}

	MoveState::~MoveState()
	{
	}

	AIState* MoveState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{

		enemyComp->HandleAI();
		gunComp->Move();




		
		//std::cout << "MOVE UPDATE";


		auto playerPhysComp = m_pPlayerComponent->GetPhysicsComp();
		auto playerPos = playerPhysComp->GetTransformComp()->GetPosition();
		auto playerWidth = playerPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto playerHeight = playerPhysComp->GetColliderComponent()->GetRectCollider().height;
		glm::vec2 playerCenter{ playerPos.x + playerWidth/2, playerPos.y + playerHeight/2 };

		auto enemyPhysComp = enemyComp->GetPhysicsComp();
		auto enemyPos = enemyPhysComp->GetTransformComp()->GetPosition();
		auto enemyWidth = enemyPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = enemyPhysComp->GetColliderComponent()->GetRectCollider().height;
		glm::vec2 enemyCenter{ enemyPos.x + enemyWidth / 2, enemyPos.y + enemyHeight / 2 };

		auto distance = glm::distance2(playerCenter, enemyCenter);
		if (distance <= 5000.0f)
		{
			std::cout << "DIST TO PLAYER FROM AI IS TOO SMALL";
			return new ShootState{ m_pPlayerComponent };
		}

		return nullptr;
		
		
	
	}

	void MoveState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		std::cout << "ON ENTER CALLED IN MOVESTATE";

		enemyComp; gunComp;
	}

	void MoveState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}


	//Shoot state


	ShootState::ShootState(PlayerComponent* playerComp) : AIState{ playerComp }
	{
	}

	ShootState::~ShootState()
	{
	}

	AIState* ShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		//std::cout << "SHOOTSTATE UPDATEEEEEEEEEEEEe" << '\n';

		auto playerPhysComp = m_pPlayerComponent->GetPhysicsComp();
		auto playerPos = playerPhysComp->GetTransformComp()->GetPosition();
		auto playerWidth = playerPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto playerHeight = playerPhysComp->GetColliderComponent()->GetRectCollider().height;
		glm::vec2 playerCenter{ playerPos.x + playerWidth / 2, playerPos.y + playerHeight / 2 };

		auto enemyPhysComp = enemyComp->GetPhysicsComp();
		auto enemyPos = enemyPhysComp->GetTransformComp()->GetPosition();
		auto enemyWidth = enemyPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = enemyPhysComp->GetColliderComponent()->GetRectCollider().height;
		glm::vec2 enemyCenter{ enemyPos.x + enemyWidth / 2, enemyPos.y + enemyHeight / 2 };

		auto distance = glm::distance2(playerCenter, enemyCenter);

		gunComp->RotateGun();
		gunComp->Shoot();

		if (distance > 5000.0f)
		{
			std::cout << "DIST TO PLAYER FROM AI IS TOO SMALL";
			return new MoveState{ m_pPlayerComponent };
		}
		else if (distance > 5000.0f)
		{
			std::cout << "DIST TO PLAYER FROM AI IS TOO SMALL";
			return new MoveState{ m_pPlayerComponent };
		}
	
		



		enemyComp; gunComp;
		return nullptr;
	}

	void ShootState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		std::cout << "CALLED ON ENTER IN SHOOT";



		enemyComp->SetVelocity(Velocity{ 0,0 });
		gunComp;
	}

	void ShootState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	//MoveAndShoot state

	MoveAndShootState::MoveAndShootState(PlayerComponent* playerComp) : AIState{ playerComp }
	{

	}

	MoveAndShootState::~MoveAndShootState()
	{
	}

	AIState* MoveAndShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp->HandleAI();
		gunComp->Move();


		//auto playerPhysComp = m_pPlayerComponent->GetPhysicsComp();
		//auto playerPos = playerPhysComp->GetTransformComp()->GetPosition();
		//auto playerWidth = playerPhysComp->GetColliderComponent()->GetRectCollider().width;
		//auto playerHeight = playerPhysComp->GetColliderComponent()->GetRectCollider().height;
		//glm::vec2 playerCenter{ playerPos.x + playerWidth / 2, playerPos.y + playerHeight / 2 };

		//auto enemyPhysComp = enemyComp->GetPhysicsComp();
		//auto enemyPos = enemyPhysComp->GetTransformComp()->GetPosition();
		//auto enemyWidth = enemyPhysComp->GetColliderComponent()->GetRectCollider().width;
		//auto enemyHeight = enemyPhysComp->GetColliderComponent()->GetRectCollider().height;
		//glm::vec2 enemyCenter{ enemyPos.x + enemyWidth / 2, enemyPos.y + enemyHeight / 2 };

		//auto distance = glm::distance2(playerCenter, enemyCenter);


		std::cout << "MOVEANDSHOOTSTATE UPDATE";

		return nullptr;
	}

	void MoveAndShootState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	void MoveAndShootState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

}