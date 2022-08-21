#pragma once
#include "BaseComponent.h"
#include <RectColliderComponent.h>
#include <PhysicsComponent.h>
#include <TileMapComponent.h>
#include <SceneManager.h>


namespace dae
{
	enum class State
	{
		normal,
		moving
	};

	class PlayerComponent : public BaseComponent
	{

	public:

		PlayerComponent(GameObject* go, PhysicsComponent* physComp/*, TileMapComponent* tileMap*/);
		~PlayerComponent();

		virtual void Update(float elapsedSec);


		void SetState(State newState);

		State GetState();

		PhysicsComponent* GetPhysicsComp();

		void Teleport();

		glm::vec2 GetPlayerCenter();

		void HandleSceneChange();


	private:


		// add transform component

		PhysicsComponent* m_pPhysicsComponent;
		//TransformComponent* m_pTransformComp;


		TileMapComponent* m_pTileMapComponent;
		State m_State;

		std::vector<std::shared_ptr<Cell>> m_CellsToCheck;

		std::shared_ptr<Cell> m_CurrentCell;

		int m_CurrentScene;

	};


}

