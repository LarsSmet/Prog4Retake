#pragma once
#include "Command.h"
#include "PlayerComponent.h"
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


		~MoveCommand(){};


		void Execute()
		{

			
		//	auto yPosCharacter = m_PlayerComp->GetPhysicsComp()->GetColliderComponent()->GetRectCollider().bottom + 17 /*+ 16*/; //plus 16 because bottom is actually left top
			//yPosCharacter;
			


			auto physComp = m_PlayerComp->GetPhysicsComp();

			if (m_Velocity.y < 0)
			{
				//std::cout << "UP";
			}
			if (m_Velocity.x < 0)
			{
				//std::cout << "left";
			}

			
			

			
				//m_CharacterComp->SetState(State::Normal);
				/*if (m_Velocity.y == 0)
				{*/
					physComp->SetVelocity(m_Velocity);
				//}
			
		}


	private:

		Velocity m_Velocity;
		PlayerComponent* m_PlayerComp;

	};
}