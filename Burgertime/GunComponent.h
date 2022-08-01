#pragma once
#include <structs.h>
#include <GameObject.h>
#include "PlayerComponent.h"
#include <Scene.h>
#include "RenderComponent.h"

namespace dae
{

	class GunComponent: public BaseComponent
	{
	public:


		GunComponent(GameObject* go, /*PhysicsComponent* physicsComp,*/ PlayerComponent* playerComp, Scene& currentScene);
		~GunComponent();


		void Update(float elapsedSec);
		void Shoot();
		void RotateGun();

	private:


		Point2f m_RotationPos;
		Point2f m_ShootPos;
		Point2f m_VectorStartPos;

		PlayerComponent* m_pPlayerComp;
		PhysicsComponent* m_pPhysicsComp;
		TransformComponent* m_pTransformComp;

		Scene& m_Scene;

		RenderComponent* m_pRenderComp;

	};


}

