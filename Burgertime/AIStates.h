#pragma once
#include "EnemyComponent.h"
#include "GunComponent.h"


namespace dae
{
	class EnemyComponent;

	class AIState
	{

	public:

		AIState() {};
		virtual ~AIState() {};
		virtual AIState* Update(EnemyComponent* comp, GunComponent* gun) { comp; gun; return nullptr; };
		virtual void OnEnter(EnemyComponent* comp, GunComponent* gun) { comp; gun; };
		virtual void OnExit(EnemyComponent* comp, GunComponent* gun) { comp; gun; };

	private:


	};

	class EnemyComponent;

	class MoveState : public AIState
	{

	public:

		MoveState();
		virtual ~MoveState();

		virtual AIState* Update(EnemyComponent* comp, GunComponent* gun) override;
		virtual void OnEnter(EnemyComponent* comp, GunComponent* gun) override;
		virtual void OnExit(EnemyComponent* comp, GunComponent* gun) override;
		



	private:



	};

	class EnemyComponent;

	class ShootState : public AIState
	{

	public:

		ShootState();
		virtual ~ShootState();

		virtual AIState* Update(EnemyComponent* comp, GunComponent* gun) override;
		virtual void OnEnter(EnemyComponent* comp, GunComponent* gun) override;
		virtual void OnExit(EnemyComponent* comp, GunComponent* gun) override;




	private:



	};


}

