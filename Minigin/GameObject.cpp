#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "RenderComponent.h"
//#include "BaseColliderComponent.h"
//#include "RectangleColliderComponent.h"
#include "TileMapComponent.h"
#include "Scene.h"
#include "SceneManager.h"

dae::GameObject::GameObject(float xPos, float yPos) : m_TransformComp{ new TransformComponent{ this, xPos, yPos} },  m_Components{}
{
	
}

dae::GameObject::~GameObject()
{
	
	//delete all components
	//std::cout << "DELETED GAMEOBJ";
	

	for (size_t i = 0; i < m_Components.size(); i++) 
	{
		delete m_Components[i];
		m_Components[i] = nullptr;
	}

	/*delete m_TransformComp;
	m_TransformComp = nullptr;*/


}

void dae::GameObject::Update(float deltaTime)
{

	//update all components

	for (auto& component : m_Components)//error when deleting bullet -> still updates some component after delete. fix in scene
	{
		
		component->Update(deltaTime);
	}



}



void dae::GameObject::Render() const
{

	auto tileMapComponent = GetComponent<TileMapComponent>();
	if (tileMapComponent != nullptr)
	{
		tileMapComponent->Render();
	}
	else
	{


		const auto& pos = m_TransformComp->GetPosition();


		std::shared_ptr<dae::Texture2D> texture;


		auto renderComponent = GetComponent<RenderComponent>();


		if (renderComponent != nullptr)
		{

			texture = renderComponent->GetTexture();

			if (renderComponent->HasRotation())
			{
				
				Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y, renderComponent->GetAngle(), renderComponent->GetRotationPoint());
				//std::cout << renderComponent->GetRotationPoint()->x << "   y: " << renderComponent->GetRotationPoint()->y << "   }";
			}
			else
			{
				Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);

			}
		}


	}

}



void dae::GameObject::SetPosition(float x, float y)
{
	m_TransformComp->SetPosition(x, y);
}

void dae::GameObject::Destroy()
{
	
	SceneManager::GetInstance().GetCurrentScene().LateRemove(shared_from_this());
	

}

void dae::GameObject::Move(float xOffSet, float yOffSet)
{
	auto pos = m_TransformComp->GetPosition();
	this->SetPosition(pos.x + xOffSet, pos.y + yOffSet);
}



void dae::GameObject::AddComponent(BaseComponent* component)
{
	
	m_Components.emplace_back(component);

}




void dae::GameObject::SetParent(std::weak_ptr<GameObject> parent)
{

	m_pParent = parent;

}


std::weak_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	
		return m_pParent;

}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}
std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{

	if (m_pChildren.size() >= 1)
	{
		return m_pChildren[index];
	}
	else
	{
		return nullptr;
	}
}
void dae::GameObject::RemoveChild(int index)
{

	m_pChildren.erase(m_pChildren.begin() + index);
}
void dae::GameObject::AddChild(std::shared_ptr<GameObject> go)
{
	m_pChildren.push_back(go);
}

dae::TransformComponent* dae::GameObject::GetTransformComp()
{
	return m_TransformComp.get();
}