#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include <chrono>
#include <memory>

#include "TextComponent.h"
#include "Font.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
//#include "PlayerComponent.h"
#include "LivesDisplayComponent.h"
#include "PointDisplayComponent.h"

#include "SoundSystem.h"



using namespace std;
namespace dae
{

	

	void PrintSDLVersion()
	{
		SDL_version compiled{};
		SDL_version linked{};

		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);
		printf("We compiled against SDL version %d.%d.%d ...\n",
			compiled.major, compiled.minor, compiled.patch);
		printf("We are linking against SDL version %d.%d.%d.\n",
			linked.major, linked.minor, linked.patch);


	}

	void dae::Minigin::Initialize()
	{
		PrintSDLVersion();
		ResourceManager::GetInstance().Init("../Data/");

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		m_Window = SDL_CreateWindow(
			"Programming 4 assignment",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			480,
			653,
			SDL_WINDOW_OPENGL
		);
		if (m_Window == nullptr)
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		Renderer::GetInstance().Init(m_Window);
	}

	/**
	 * Code constructing the scene world starts here
	 */
	void dae::Minigin::LoadGame() const
	{

	

		//auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	


		//auto go = std::make_shared<GameObject>();
		//RenderComponent* renderComponent = new RenderComponent{};

		//renderComponent->SetTexture("background.jpg");
		////go->SetTexture("background.jpg");
		//go->AddComponent(renderComponent);
		//scene.Add(go);

		//go = std::make_shared<GameObject>();
		////go->SetTexture("logo.png");
		//renderComponent = new RenderComponent{};
		//renderComponent->SetTexture("logo.png");
		//go->AddComponent(renderComponent);
		//go->SetPosition(216, 180);
		//scene.Add(go);

		//SDL_Color white{ 255,255,255 };

		//go = std::make_shared<GameObject>();
		//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		//std::string text = "Programming 4 Assignment";
		//renderComponent = new RenderComponent{};
		//go->AddComponent(renderComponent);
		//TextComponent* textComponent = new TextComponent{ text, font, renderComponent, white };
		//go->SetPosition(80, 20);
		//go->AddComponent(textComponent);
		//scene.Add(go);

		//go = std::make_shared<GameObject>();
		//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
		//text = "Press X to end the program, press A to make the player die";
		//renderComponent = new RenderComponent{};
		//go->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, white };
		//go->SetPosition(10, 120);
		//go->AddComponent(textComponent);
		//scene.Add(go);

		//go = std::make_shared<GameObject>();
		//text = "Press B to make an enemy die and play a sound, press Y to make a burger drop";
		//renderComponent = new RenderComponent{};
		//go->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, white };
		//go->SetPosition(10, 140);
		//go->AddComponent(textComponent);
		//scene.Add(go);




		//
		//int startLives{ 3 };
		//int startPoints{ 0 };

		//SDL_Color player1Col{ 255,255,0 };

		//////player1
		//auto player1 = std::make_shared<GameObject>();
		//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);

		//PlayerComponent* peterPepperComponent = new PlayerComponent{ startLives,startPoints };


		////lives
		//auto livesDisplay = std::make_shared<GameObject>();
		//text = "Lives: " + std::to_string(startLives);
		//renderComponent = new RenderComponent{};
		//livesDisplay->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, player1Col };
		//livesDisplay->SetPosition(10, 250);

		//LivesDisplayComponent* livesDisplayComponent = new LivesDisplayComponent{ textComponent, peterPepperComponent };

		//livesDisplay->AddComponent(textComponent);
		//livesDisplay->AddComponent(livesDisplayComponent);
		//scene.Add(livesDisplay);


		////points
		//auto pointsDisplay = std::make_shared<GameObject>();
		//text = "Points: " + std::to_string(startPoints);
		//renderComponent = new RenderComponent{};
		//pointsDisplay->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, player1Col };
		//pointsDisplay->SetPosition(10, 350);


		//PointsDisplayComponent* pointsDisplayComponent = new PointsDisplayComponent{ textComponent, peterPepperComponent };

		//pointsDisplay->AddComponent(textComponent);
		//pointsDisplay->AddComponent(pointsDisplayComponent);
		//scene.Add(pointsDisplay);

		//peterPepperComponent->AddObserver(livesDisplayComponent);
		//peterPepperComponent->AddObserver(pointsDisplayComponent);
		//player1->AddComponent(peterPepperComponent);

		//scene.Add(player1);

		////player 2
		//SDL_Color player2Col{ 0,255,0 };
		//
		//auto player2 = std::make_shared<GameObject>();
		//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);

		//PlayerComponent* sallySaltComponent = new PlayerComponent{ startLives,startPoints };


		////lives
		// livesDisplay = std::make_shared<GameObject>();
		//text = "Lives: " + std::to_string(startLives);
		//renderComponent = new RenderComponent{};
		//livesDisplay->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, player2Col };
		//livesDisplay->SetPosition(500, 250);

		//livesDisplayComponent = new LivesDisplayComponent{ textComponent, sallySaltComponent };

		//livesDisplay->AddComponent(textComponent);
		//livesDisplay->AddComponent(livesDisplayComponent);
		//scene.Add(livesDisplay);


		////points
		//pointsDisplay = std::make_shared<GameObject>();
		//text = "Points: " + std::to_string(startPoints);
		//renderComponent = new RenderComponent{};
		//pointsDisplay->AddComponent(renderComponent);
		//textComponent = new TextComponent{ text, font, renderComponent, player2Col };
		//pointsDisplay->SetPosition(500, 350);


		//pointsDisplayComponent = new PointsDisplayComponent{ textComponent, sallySaltComponent };

		//pointsDisplay->AddComponent(textComponent);
		//pointsDisplay->AddComponent(pointsDisplayComponent);
		//scene.Add(pointsDisplay);

		//sallySaltComponent->AddObserver(livesDisplayComponent);
		//sallySaltComponent->AddObserver(pointsDisplayComponent);
		//player2->AddComponent(sallySaltComponent);

		//scene.Add(player2);
		//
		//

		//



		//dae::InputManager& inputManager = dae::InputManager::GetInstance();
		////keys
		//ControllerKey akey{ int(dae::ControllerButton::ButtonA), dae::ControllerButton::ButtonA };
		//std::shared_ptr<PlayerDeathCommand> playerDeath = std::make_shared<PlayerDeathCommand>(*peterPepperComponent);
		//inputManager.BindKey(akey, playerDeath);


		//ControllerKey bkey{ int(dae::ControllerButton::ButtonB), dae::ControllerButton::ButtonB };
		//std::shared_ptr<EnemyDeathCommand> enemyDeath = std::make_shared<EnemyDeathCommand>(*peterPepperComponent);
		//inputManager.BindKey(bkey, enemyDeath);

		//ControllerKey ykey{ int(dae::ControllerButton::ButtonY), dae::ControllerButton::ButtonY };
		//std::shared_ptr<BurgerDropCommand> burgerDrop = std::make_shared<BurgerDropCommand>(*peterPepperComponent);
		//inputManager.BindKey(ykey, burgerDrop);

	


	}

	void dae::Minigin::Cleanup()
	{
		Renderer::GetInstance().Destroy();
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
		SDL_Quit();
	}

	void dae::Minigin::Run()
	{
#if _DEBUG
		ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDLSoundSystem()));
#else
		ServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif





		auto& mySoundSystem = ServiceLocator::GetSoundSystem();


		{


			dae::InputManager& inputManager = dae::InputManager::GetInstance();



			auto& renderer = Renderer::GetInstance();
			auto& sceneManager = SceneManager::GetInstance();
		
			auto lastTime = chrono::high_resolution_clock::now();
			float lag = 0.0f;

			float fixedTimeStep = 0.02f;
			float msPerUpdate = 0.1f;

			bool doContinue = true;

			//gameloop
			while (doContinue)
			{

				doContinue = inputManager.ProcessInput();
				inputManager.HandleInput();



				const auto currentTime = chrono::high_resolution_clock::now();
				float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
				
				lastTime = currentTime;
				lag += deltaTime;



				while (lag >= msPerUpdate)
				{
					FixedUpdate(fixedTimeStep);
					lag -= fixedTimeStep;
				}


				sceneManager.Update(deltaTime);
				renderer.Render();




				mySoundSystem.Update();

			}



		}

		ServiceLocator::DeleteSoundSystem();



		Cleanup();
	}

	void dae::Minigin::FixedUpdate(float fixedTimeStep)
	{
		fixedTimeStep;
	}

}