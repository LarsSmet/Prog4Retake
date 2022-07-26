#include "MiniginPCH.h"
#include "FPSComponent.h"



dae::FPSComponent::FPSComponent(GameObject* go):BaseComponent(go)
{

}
void dae::FPSComponent::Update(float deltaTime)
{

	uint64_t countsPerSecond = SDL_GetPerformanceFrequency();
	
	if (m_ElapsedTime < 0.0f)
	{
		m_ElapsedTime = 0.0f;
	}
	m_ElapsedTime = deltaTime * (1.0f / countsPerSecond);


}


int dae::FPSComponent::CalculateFPS()
{

	//src: partially used from graphics prog 1 raytracer framework
	m_FPSTimer += m_ElapsedTime;
	++m_FPSCount;
	if (m_FPSTimer >= 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FPSTimer -= 1.0f;
	}

	return m_FPS;
}

