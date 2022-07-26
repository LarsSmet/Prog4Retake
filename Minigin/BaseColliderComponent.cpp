#include "MiniginPCH.h"
#include "BaseColliderComponent.h"

namespace dae
{

	BaseColliderComponent::BaseColliderComponent(GameObject* go, bool isTrigger) : BaseComponent{ go }, m_IsTrigger{ isTrigger }
	{

	}

	BaseColliderComponent::~BaseColliderComponent()
	{
		
	}

	Rectf* BaseColliderComponent::GetRectCollider() const
	{

		return nullptr;

	}

	Circlef* BaseColliderComponent::GetCircleCollider() const
	{
		return nullptr;
	}

	std::vector<std::vector<Point2f>>* BaseColliderComponent::GetVerticesCollider() const
	{
		return nullptr;
	}

	

	

}
