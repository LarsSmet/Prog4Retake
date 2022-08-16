#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include "PlayerComponent.h"
#include "AIStates.h"



namespace dae
{
	class AIStates;
	class GunComponent;
	

	class EnemyComponent : public BaseComponent
	{

	public:

		EnemyComponent(GameObject* go, PhysicsComponent* physComp, TileMapComponent* tileMap, PlayerComponent* playerComp);
		~EnemyComponent();
		virtual void Update(float elapsedSec) override;

		void HandleAI();

		void SetVelocity(Velocity newVelocity);


		
		
	



		PhysicsComponent* GetPhysicsComp();

		void ResetVelocity();

		Velocity GetVelocity();


	private:

		/*AIState* m_State;*/

		PhysicsComponent* m_pPhysicsComponent;


		TileMapComponent* m_pTileMapComponent;

		std::vector<std::shared_ptr<Cell>> m_CellsToCheck;

		std::shared_ptr<Cell> m_CurrentCell;

		
		PlayerComponent* m_pPlayerComponent;

		GunComponent* m_pGunComponent;

		AIState* m_pAIState;

		


	};





}