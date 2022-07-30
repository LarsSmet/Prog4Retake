#include "MiniginPCH.h"
#include "TransformComponent.h"

//i did not make this myself.
//SOURCE: HOWEST DAE Programming 2 files 

namespace dae
{

	

	TransformComponent::TransformComponent(GameObject* go, float xPos, float yPos):BaseComponent(go), m_Position{xPos, yPos}
	{

	}
	void TransformComponent::Update(float deltaTime)
	{
		deltaTime;
	}

	void TransformComponent::SetXPosition(const float x)
	{
		m_Position.x = x;
	
	}
	void TransformComponent::SetYPosition( const float y)
	{

		m_Position.y = y;

	
	}

	void TransformComponent::SetPosition(const float x, const float y)
	{
		m_Position.x = x;
		m_Position.y = y;
		
		//std::cout << m_Position.x;
	}

	void TransformComponent::Move(float xOffSet, float yOffSet)
	{
		
		SetPosition(m_Position.x + xOffSet, m_Position.y + yOffSet);
	}

	glm::vec2 TransformComponent::GetPosition() const
	{

		//std::cout << m_Position.x;
		return m_Position;
	}

}