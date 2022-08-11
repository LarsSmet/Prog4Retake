#pragma once
#include "Command.h"
#include "PlayerComponent.h"
#include "GunComponent.h"
namespace dae
{

	class GameCommands
	{
	};

	class MoveCommand : public Command
	{

	public:


		MoveCommand(PlayerComponent* playerComp, float xSpeed, float ySpeed) : m_PlayerComp{ playerComp }, m_Velocity{ xSpeed, ySpeed }
		{

		};


		~MoveCommand() {};


		void Execute()
		{


			//	auto yPosCharacter = m_PlayerComp->GetPhysicsComp()->GetColliderComponent()->GetRectCollider().bottom + 17 /*+ 16*/; //plus 16 because bottom is actually left top
				//yPosCharacter;
				//std::cout << m_Velocity.y;


			auto physComp = m_PlayerComp->GetPhysicsComp();

			if (m_Velocity.y < 0)
			{
				//std::cout << "UP";
			}
			if (m_Velocity.y > 0)
			{
				//std::cout << "down";
			}





			//m_CharacterComp->SetState(State::Normal);
			/*if (m_Velocity.y == 0)
			{*/
			physComp->SetVelocity(m_Velocity);
			//}

				//std::cout << m_Velocity.y;

		}


	private:

		Velocity m_Velocity;
		PlayerComponent* m_PlayerComp;

	};



	class ShootCommand : public Command
	{

	public:


		ShootCommand(GunComponent* gunComp) : m_GunComp{ gunComp }
		{

		};
		~ShootCommand() {};

		void Execute()
		{
			std::cout << "Shoot";
			m_GunComp->Shoot();
		}

	private:

		GunComponent* m_GunComp;

	};


}