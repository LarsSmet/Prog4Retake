#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include "GameObject.h"
namespace dae
{
	enum class GunOwner
	{
		player,
		enemy
	};


	class BulletComponent : public BaseComponent 
	{
	public:
		BulletComponent(GameObject* go, PhysicsComponent* physicsComp, TileMapComponent* tileMap, GunOwner gunOwner);
		~BulletComponent();

		void Update(float elapsedSec);

		void SetVelocity(Velocity velocity);

	
		


	private:

		PhysicsComponent* m_pPhysicsComponent;
		Velocity m_Velocity;

		int m_BounceCounter;

		TileMapComponent* m_pTileMapComponent;

		std::shared_ptr<Cell> m_CurrentCell;
		std::vector<std::shared_ptr<Cell>> m_CellsToCheck{};


		bool m_KillBullet;

		void HandleBounce();
		void HandleDamage();
		void KillBullet();

		GunOwner m_GunOwner;

	};


}
