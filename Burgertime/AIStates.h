#pragma once
//#include "EnemyComponent.h"
//#include "GunComponent.h"


namespace dae
{
	class EnemyComponent;
	class GunComponent;

	class AIState
	{

	public:

		AIState() {};
		virtual ~AIState() {};
		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; return nullptr; };
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; };
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) { enemyComp; gunComp; };

	private:


	};

	class EnemyComponent;

	class MoveState : public AIState
	{

	public:

		MoveState();
		virtual ~MoveState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		



	private:



	};

	class EnemyComponent;

	class ShootState : public AIState
	{

	public:

		ShootState();
		virtual ~ShootState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;




	private:



	};

	class EnemyComponent;

	class MoveAndShootState : public AIState
	{

	public:

		MoveAndShootState();
		virtual ~MoveAndShootState();

		virtual AIState* Update(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnEnter(EnemyComponent* enemyComp, GunComponent* gunComp) override;
		virtual void OnExit(EnemyComponent* enemyComp, GunComponent* gunComp) override;




	private:



	};


}

