#pragma once
#include "BaseComponent.h"
#include "utils.h"
namespace dae
{
	class RectColliderComponent : public BaseComponent
	{

	public:

		RectColliderComponent(GameObject* go);
		~RectColliderComponent();

		//CollisionHitInfo OnCollision(BaseColliderComponent* collision);

		void SetPosition();
		Point2f GetPosition() const;
		void Move(float xOffSet, float yOffSet);

	private:


	};

}

