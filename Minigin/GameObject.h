#pragma once
//#include "Transform.h"

#include "SceneObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include <vector>
#include "BaseColliderComponent.h"
//#include "RectangleColliderComponent.h"
#include "utils.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final 
	{
	public:

		
		void Update(float deltaTime);
		void Render() const;

		
		void SetPosition(float x, float y);


		//template <typename T> 
		void AddComponent(BaseComponent* component);
		template <typename T>
		inline T* GetComponent() const // wrong and not finished
		{
			for (auto& component : m_Components) //improve by using std::find or std::find_if?
			{


				T* casted = dynamic_cast<T*>(component);
				if (casted != nullptr)
				{
					return casted;
				}
				else
				{

				}



				component;
			}

			return nullptr;

		}
		//template <typename T> 
		template <typename T>
		void RemoveComponent(T*)
		{
			//auto it = std::find(m_Components.begin(), m_Components.end(), T);

			//m_Components.erase(it);

			//T* temp;
			//temp = GetComponent<T>();
			//if (temp != nullptr)
			//{
			//	/*m_Components.swap(temp, m_Components.end());
			//	delete temp;
			//	m_Components.pop_back();*/
			//	
			//	
			//}

			auto comp = GetComponent<T>();

			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), comp), m_Components.end());


			//add something that delets the pointer

		}



		void SetParent(std::weak_ptr<GameObject> parent);


		std::weak_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(int index) const;
		void RemoveChild(int index);
		void AddChild(std::shared_ptr<GameObject> go);

		void Move(float xOffSet, float yOffSet);
		TransformComponent* GetTransformComp();

		GameObject(float xPos, float yPos);
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		//Transform m_Transform;
		

		std::vector<BaseComponent*> m_Components;
		std::vector<BaseComponent*> m_ComponentsTrash;


		std::weak_ptr<GameObject> m_pParent;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;

		TransformComponent* m_TransformComp;

	};
}
