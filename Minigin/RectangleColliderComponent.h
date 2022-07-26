#pragma once
#include "BaseColliderComponent.h"
#include "utils.h"
namespace dae
{



	class RectangleColliderComponent final : public BaseColliderComponent
	{
	public:

		RectangleColliderComponent(GameObject* go, bool isTrigger, Rectf* colliderShape);
		~RectangleColliderComponent();


		virtual CollisionHitInfo OnCollision(BaseColliderComponent* collision) override; 
	

		virtual bool OnTrigger(BaseColliderComponent* collision) override; 


		virtual void SetPosition(const float x, const float y);
		virtual void Move(float xOffSet, float yOffSet);

		 Rectf* GetRectCollider() const override;
		 virtual Point2f GetPosition() const override;


	protected:

		

	private:


		Rectf* m_pCollider; 
		
	};
}

