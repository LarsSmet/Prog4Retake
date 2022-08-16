#include "pch.h"
#include "AIStates.h"
#include "EnemyComponent.h"
#include "GunComponent.h"
namespace dae
{
	//Move state

	MoveState::MoveState()
	{
	}

	MoveState::~MoveState()
	{
	}

	AIState* MoveState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{

		enemyComp->HandleAI();
		gunComp->Move();
		
		std::cout << "MOVE UPDATE";
		return nullptr;
	
	}

	void MoveState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	void MoveState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}


	//Shoot state


	ShootState::ShootState()
	{
	}

	ShootState::~ShootState()
	{
	}

	AIState* ShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		std::cout << "SHOOTSTATE UPDATE";

		enemyComp; gunComp;
		return nullptr;
	}

	void ShootState::OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp->SetVelocity(Velocity{ 0,0 });
		gunComp;
	}

	void ShootState::OnExit(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp; gunComp;
	}

	//MoveAndShoot state

	MoveAndShootState::MoveAndShootState()
	{

	}

	MoveAndShootState::~MoveAndShootState()
	{
	}

	AIState* MoveAndShootState::Update(EnemyComponent* enemyComp, GunComponent* gunComp)
	{
		enemyComp->HandleAI();
		gunComp->Move();

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