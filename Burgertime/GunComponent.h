#pragma once
#include <structs.h>
#include <GameObject.h>
#include "PlayerComponent.h"
#include <Scene.h>
#include "RenderComponent.h"
#include "BulletComponent.h"
//#include "EnemyComponent.h"

namespace dae
{
	class EnemyComponent;

	class GunComponent: public BaseComponent
	{
	public:


		GunComponent(GameObject* go, PlayerComponent* playerComp, EnemyComponent* enemyComp, Scene& currentScene, TileMapComponent* tileMap);
		~GunComponent();


		void Update(float elapsedSec);
		void Move();
		void Shoot();
		void RotateGun();

	private:


		Point2f m_RotationPos;
		Point2f m_ShootPos;
		Point2f m_VectorStartPos;

		PlayerComponent* m_pPlayerComp;
		EnemyComponent* m_pEnemyComp;
		PhysicsComponent* m_pPhysicsComp;
		TransformComponent* m_pTransformComp;

		Scene& m_Scene;

		RenderComponent* m_pRenderComp;

		TileMapComponent* m_pTileMap;

		bool m_OwnedByPlayer;

		GunOwner m_GunOwner;

	};


}

