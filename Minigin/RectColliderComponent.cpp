#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

namespace dae
{
	RectColliderComponent::RectColliderComponent(GameObject* go) : BaseComponent(go)
	{

	}

	RectColliderComponent::~RectColliderComponent()
	{

	}
	//CollisionHitInfo RectColliderComponent::OnCollision(BaseColliderComponent* collision)
	//{
	//	return CollisionHitInfo();
	//}


	void RectColliderComponent::SetPosition()
	{

	}

	Point2f RectColliderComponent::GetPosition() const
	{
		return Point2f();
	}
	void RectColliderComponent::Move(float xOffSet, float yOffSet)
	{
		xOffSet;
		yOffSet;
	}
}