#pragma once
#include "BaseComponent.h"
#include "MiniginPCH.h"

namespace dae
{

	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(GameObject* go, float xPos, float yPos);
		void Update(float deltaTime) override;

		void SetXPosition(const float x);

		void SetYPosition(const float y);

		void SetPosition(const float x, const float y);
		void Move(float xOffSet, float yOffSet);
		glm::vec2 GetPosition() const;



	private:
		//vec 2 because it is 2d
		glm::vec2 m_Position;


	};

}