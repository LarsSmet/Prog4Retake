#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.emplace_back(object);
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}

	////check if objects to delete, if so delete them and remove it from the vector with remove/erase
	////also do it for entitymanager

	//add gameobjects
	if (!m_LateObjectsToAdd.empty()) //if we have gameobjects to add
	{
		for (const auto& objectToAdd: m_LateObjectsToAdd)
		{
			m_Objects.emplace_back(objectToAdd);
		}
		m_LateObjectsToAdd.clear();

	}

}

void Scene::LateAdd(const std::shared_ptr<GameObject>& object)
{
	m_LateObjectsToAdd.emplace_back(object);
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

