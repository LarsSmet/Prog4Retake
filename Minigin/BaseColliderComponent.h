#pragma once
#include "BaseComponent.h"
#include "utils.h"
namespace dae
{

	struct CollisionHitInfo
	{
		utils::HitInfo hitInfoHorizontal;
		utils::HitInfo hitInfoVertical;
		bool horizontalHit = false;
		bool verticalHit = false;
		bool leftHit = false;
		bool rightHit = false;
		bool botHit = false;
		bool topHit = false;

	};

	class BaseColliderComponent : public BaseComponent
	{

	public:

		BaseColliderComponent(GameObject* go, bool isTrigger);
		virtual ~BaseColliderComponent();


		virtual CollisionHitInfo OnCollision(BaseColliderComponent* collision) = 0; //with raycast
		

		virtual bool OnTrigger(BaseColliderComponent* collision) = 0; //with overlapping

		virtual void SetPosition(const float x, const float y) = 0;
		virtual void Move(float xOffSet, float yOffSet) = 0;

		virtual Rectf* GetRectCollider() const;
		virtual Circlef* GetCircleCollider() const;
		virtual std::vector<std::vector<Point2f>>* GetVerticesCollider() const;

		virtual Point2f GetPosition() const = 0;

	protected:

		bool m_IsTrigger;

	private:

	};

}

