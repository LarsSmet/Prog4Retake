#pragma once
#include "BaseComponent.h"
#include <PhysicsComponent.h>

namespace dae
{

	class BulletComponent : public BaseComponent 
	{
	public:
		BulletComponent(GameObject* go, PhysicsComponent* physicsComp);
		~BulletComponent();

		void Update(float elapsedSec);

		void SetVelocity(Velocity velocity);

		void HandleBounce();


	private:

		PhysicsComponent* m_pPhysicsComp;
		Velocity m_Velocity;


	};


}
