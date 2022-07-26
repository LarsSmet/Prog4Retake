#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"


dae::RenderComponent::RenderComponent(GameObject* go) : BaseComponent{go}
{

}

dae::RenderComponent::~RenderComponent()
{

}
void dae::RenderComponent::Update(float deltaTime)
{
	deltaTime;
	
	
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
	m_Texture = texture;
}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture()
{
	return m_Texture;

	
}