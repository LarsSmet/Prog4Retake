#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{

	class PlayerComponent final: public BaseComponent, public Subject
	{

	public:

		PlayerComponent(GameObject* go, int lives, int startPoints);
		~PlayerComponent();
		void Update(float) override;
		void KillPlayer();
		void AddPoints(int value, Event event);


		int GetLives();
		int GetPoints();

	private:

		int m_Lives;

		int m_Points;


	};

}