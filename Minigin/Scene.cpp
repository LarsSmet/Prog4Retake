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


	if (!m_LateObjectsToRemove.empty()) //if we have gameobjects to remove
	{
		//https://stackoverflow.com/questions/799314/difference-between-erase-and-remove
		// https://makeinjava.com/stl-erase-remove-idiom-c-example/
		//!emove doesn't delete -> puts element on the end of the vector and size stays the same!
		

		auto startOfErase = m_Objects.end(); //use this instead of m_Objects.end in remove if.
		//this tracks the startpos of the erase, cant use something like a regular for loop with a counter
		//because if the object is not found, remove if returns iterator to last element of the vector and the counter would still increase


		for (const auto& objectToRemove : m_LateObjectsToRemove)
		{
			//only checks until startpos of the erase, if new element to delete to remove has been found, change teh startpos of the erare
			startOfErase = std::remove_if(m_Objects.begin(), startOfErase, [objectToRemove](const std::shared_ptr<GameObject >& go){return go == objectToRemove;});
				

				

		}

		m_Objects.erase(startOfErase, m_Objects.end()); //remove all objects an once instead of seperately

		m_LateObjectsToRemove.clear();

	}


}

void Scene::LateAdd(const std::shared_ptr<GameObject>& object)
{
	m_LateObjectsToAdd.emplace_back(object);
}

void Scene::LateRemove(const std::shared_ptr<GameObject>& object)
{

	m_LateObjectsToRemove.emplace_back(object);

}


void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

