#include "MiniginPCH.h"
#include "PointDisplayComponent.h"
#include "TextComponent.h"
#include "Event.h"
#include <iostream>

namespace dae
{


	PointsDisplayComponent::PointsDisplayComponent(GameObject* go, TextComponent* textComp) : BaseComponent{ go }, m_pTextComp { textComp }/*, m_PlayerComp{ peterPepperComponent }*/
	{

	}

	void PointsDisplayComponent::onNotify(Event event)
	{
		if (m_pTextComp == nullptr)
		{
			return;
		}
		event;

		//switch (event)
		//{
		//case Event::PlayerDied:


		//	break;
		//case Event::EnemyDied:

		//	//m_pTextComp->SetText("Points: " + std::to_string(m_PlayerComp->GetPoints()));

		//	break;
		//case Event::BurgerDropped:

		//	//m_pTextComp->SetText("Points: " + std::to_string(m_PlayerComp->GetPoints()));

		//	break;

		//}

	}

	void PointsDisplayComponent::Update(float)
	{
	}



}