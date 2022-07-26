#pragma once
#include "BaseComponent.h"


namespace dae
{
	class FPSComponent final : public BaseComponent
	{


	public:

		FPSComponent(GameObject* go);
		void Update(float deltaTime) override;


	private:

		int CalculateFPS();
	
		int m_FPS;
		
		int m_FPSCount;

		float m_ElapsedTime = 0.0f;
		float m_SecondsPerCount = 0.0f;
		
		float m_FPSTimer = 0.0f;

	};

}
