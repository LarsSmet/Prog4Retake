#include "MiniginPCH.h"
#include "PlayerComponent.h"

namespace dae
{

	PlayerComponent::PlayerComponent(GameObject* go, int lives, int startPoints) : BaseComponent(go), m_Lives{ lives }, m_Points{ startPoints }
	{

	}

	PlayerComponent::~PlayerComponent()
	{
	}

	void PlayerComponent::Update(float)
	{

	}

	void PlayerComponent::KillPlayer()
	{
		--m_Lives;
		if (m_Lives >= 0)
		{

			Notify(Event::PlayerDied);
		}


	}

	void PlayerComponent::AddPoints(int value, Event event)
	{
		m_Points += value;

		switch (event)
		{
		case Event::EnemyDied:

			Notify(Event::EnemyDied);

			break;
		case Event::BurgerDropped:

			Notify(Event::BurgerDropped);

			break;

		}



	}

	int PlayerComponent::GetLives()
	{
		return m_Lives;
	}

	int PlayerComponent::GetPoints()
	{
		return m_Points;
	}

}