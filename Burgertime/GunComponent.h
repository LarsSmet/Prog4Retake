#pragma once
#include <structs.h>
#include <GameObject.h>
#include "PlayerComponent.h"

namespace dae
{

	class GunComponent: public BaseComponent
	{
	public:


		GunComponent(GameObject* go, /*PhysicsComponent* physicsComp,*/ PlayerComponent* playerComp);
		~GunComponent();


		void Update(float elapsedSec);
		void Shoot();
		void RotateGun();

	private:


		Point2f m_RotationPos;
		Point2f m_ShootPos;

		PlayerComponent* m_pPlayerComp;
		PhysicsComponent* m_pPhysicsComp;
		TransformComponent* m_pTransformComp;

	};


}

