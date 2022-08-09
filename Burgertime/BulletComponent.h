#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include "GameObject.h"
namespace dae
{

	class BulletComponent : public BaseComponent 
	{
	public:
		BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap);
		~BulletComponent();

		void Update(float elapsedSec);

		void SetVelocity(Velocity velocity);

		void HandleBounce();


	private:

		PhysicsComponent* m_pPhysicsComponent;
		Velocity m_Velocity;

		int m_BounceCounter;

		TileMapComponent* m_pTileMapComponent;

		std::shared_ptr<Cell> m_CurrentCell;
		std::vector<std::shared_ptr<Cell>> m_CellsToCheck;


	};


}
