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

			std::cout << "CALLED THE MOVE COMMAND BY PRESSING ONCE" << '\n';


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



			auto& ss = ServiceLocator::GetSoundSystem();


			const char* path = "../Data/DeathSound.wav";
			int volume = 10;
			ss.PlaySoundRequest(SoundRequest{path, volume});

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
			std::cout << "CALLED THESHOOT COMMAND BY PRESSING ONCE" << '\n';
			m_GunComp->Shoot();
		}

	private:

		GunComponent* m_GunComp;

	};



	class RotateGunCommand : public Command
	{

	public:


		RotateGunCommand(GunComponent* gunComp) : m_GunComp{ gunComp }
		{

		};
		~RotateGunCommand() {};

		void Execute()
		{
			
			m_GunComp->RotateGun();
		}

	private:

		GunComponent* m_GunComp;

	};


}