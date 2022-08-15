#include "pch.h"
#include "AIStates.h"

namespace dae
{




	MoveState::MoveState()
	{
	}

	MoveState::~MoveState()
	{
	}

	AIState* MoveState::Update(EnemyComponent* comp, GunComponent* gun)
	{

		comp->HandleAI();
		gun;
		//do raycast to find player
		//if hit player-> aim -> shoot

		return new AIState;
	
	}

	void MoveState::OnEnter(EnemyComponent* comp, GunComponent* gun)
	{
		comp; gun;
	}

	void MoveState::OnExit(EnemyComponent* comp, GunComponent* gun)
	{
		comp; gun;
	}




}