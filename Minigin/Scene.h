#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(float deltaTime);
		void LateAdd(const std::shared_ptr<GameObject>& object);
		void LateRemove(const std::shared_ptr<GameObject>& object);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};
		std::vector < std::shared_ptr<GameObject>> m_LateObjectsToAdd{};
		std::vector < std::shared_ptr<GameObject>> m_LateObjectsToRemove{};

		static unsigned int m_IdCounter; 
	
	
	
	
	};

}
