#pragma once
#include "BaseComponent.h"
#include <RectColliderComponent.h>


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

		PlayerComponent(GameObject* go, RectColliderComponent collider);
		~PlayerComponent();

		virtual void Update(float elapsedSec);


		void SetState(State newState);

		State GetState();


	private:


		// add transform component

		RectColliderComponent m_Collider;
		State m_State;


	};


}

