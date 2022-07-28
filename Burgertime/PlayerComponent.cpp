#include "pch.h"
#include "PlayerComponent.h"
#include "GameObject.h"

namespace dae
{



	PlayerComponent::PlayerComponent(GameObject* go, RectColliderComponent collider): BaseComponent{ go }, m_Collider{collider}
	{

	}

	PlayerComponent::~PlayerComponent()
	{
	}

	void PlayerComponent::Update(float elapsedSec)
	{
		elapsedSec;

		//handle collision
		//handle move commands


	}

	void PlayerComponent::SetState(State newState)
	{
		newState;
	}

	State PlayerComponent::GetState()
	{
		return m_State;
	}

}