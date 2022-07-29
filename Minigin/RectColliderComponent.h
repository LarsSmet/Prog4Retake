#pragma once
#include "BaseComponent.h"
#include "utils.h"
namespace dae
{

	struct CollisionHitInfo
	{
	
		//left col hitinfo
		utils::HitInfo leftColBot;
		utils::HitInfo leftColTop;

		//top col hitinfo
		utils::HitInfo topColLeft;
		utils::HitInfo topColRight;

		//right col hitinfo
		utils::HitInfo rightColTop;
		utils::HitInfo rightColBot;

		//bot col hitinfo
		utils::HitInfo botColRight;
		utils::HitInfo botColLeft;


	};


	class RectColliderComponent : public BaseComponent
	{

	public:

		RectColliderComponent(GameObject* go);
		~RectColliderComponent();

		CollisionHitInfo OnCollision(RectColliderComponent* collision);

		void SetPosition();
		Point2f GetPosition() const;
		void Move(float xOffSet, float yOffSet);

		Rectf* GetRectCollider();


	private:



		Rectf* m_RectCollider;


	};

}

