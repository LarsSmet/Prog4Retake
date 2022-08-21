#include "pch.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

namespace dae
{

	ScoreComponent::ScoreComponent(GameObject* go, TextComponent* display) : BaseComponent{ go }, m_pTextComponent{display}, m_Score{0}
	{

	}


	ScoreComponent::~ScoreComponent()
	{

	}

	void ScoreComponent::onNotify(Event event)
	{

		switch (event)
		{
		case Event::PlayerDied:
			break;
		case Event::EnemyDied:
			break;
	
		default:
			break;
		}

	}

	void ScoreComponent::ChangeScore(int change)
	{
		m_Score += change;
		m_pTextComponent->SetText(std::to_string(m_Score));

	}


	


}