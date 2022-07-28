#include "pch.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SDL_opengl.h"
#include <Scene.h>
#include <RenderComponent.h>
#include <ResourceManager.h>
#include <TextComponent.h>
#include <LivesDisplayComponent.h>
#include <PointDisplayComponent.h>
#include <InputManager.cpp>
//#include <RectangleColliderComponent.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "SDL_opengl.h"
#include "utils.h"
#include <PhysicsComponent.h>
//#include "CharacterComponent.h"
#include "Texture2D.h"
#include <VerticesCollider.h>
#include <SVGParser.cpp>
#include <TileMapComponent.h>
//#include "GameCommands.h"
//#include "BurgerPartComponent.h"
//#include "GameMode.h"
//#include "GameMode.h"
//#include "EnemyComponent.h"


using namespace dae;
void LoadGame();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	LoadGame();

	engine.Run();
	return 0;



}



void LoadGame()
{
	ResourceManager::GetInstance().Init("../Data/");

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	scene;

	//auto gameModeGo = std::make_shared<GameObject>(0.f, 0.f);
	//GameMode* gameModeComponent = new GameMode{ gameModeGo.get()};
	//gameModeGo->AddComponent(gameModeComponent);




	float playerStartx = 0;
	float playerStartY = 0;

	//auto go = std::make_shared<GameObject>(playerStartx, playerStartY);

	//RenderComponent* renderComponent = new RenderComponent{ go.get()};

	//renderComponent->SetTexture("WallTile.png");
	//go->AddComponent(renderComponent);

	//scene.Add(go);


	auto go = std::make_shared<GameObject>(playerStartx, playerStartY);


	

	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/TileMap.txt" };

	//std::ifstream input;
	//
	//input.open("../Data/TileMap.txt");

	//if (!input.is_open())
	//{
	//	std::cout << "Opening file failedsssssssssssssss";
	//	return;
	//}

	//tileMapComponent;

	tileMapComponent->ConvertFileToMap();

	//tileMapComponent.ConvertFileToMap();
	go->AddComponent(tileMapComponent);

	scene.Add(go);

	////auto test = go->GetComponent<RenderComponent>();
	////go->RemoveComponent<RenderComponent>(renderComponent);
	//
	//if (go->GetComponent<RenderComponent>() == nullptr)
	//{
	//	std::cout << "it worked :)";

	//}

	//std::cout << "test123";
	//auto texture = renderComponent->GetTexture()->GetSDLTexture();
	//

	//SDL_Point size;

	//SDL_QueryTexture(texture, nullptr,nullptr, &size.x, &size.y);


	////make col components
	//Rectf* playerShape = new Rectf{ playerStartx,playerStartY /*+ float(size.y)*/, float(size.x),float( size.y) };
	////second rectf argument needs to be y + size(16) because loaded from left top
	//std::cout << size.x << "  " << size.y;

	//RectangleColliderComponent* playerCollider = new RectangleColliderComponent{ go.get(), false, playerShape };



	////go 2
	//float startPosGO2x = 0;
	//float startPosGO2y = 0;
	//auto go2 = std::make_shared<GameObject>(startPosGO2x, startPosGO2y);
	//RenderComponent* renderComponentLevel = new RenderComponent{ go2.get() };
	//renderComponentLevel->SetTexture("LevelTexture.png");
	//go2->AddComponent(renderComponentLevel);

	//std::vector<std::vector<Point2f>> levelSVG;

	//SVGParser::GetVerticesFromSvgFile("../Data/LevelSVG.svg", levelSVG);

	//std::vector<std::vector<Point2f>>* pLevelVertices  = new std::vector<std::vector<Point2f>>{levelSVG};




	//VerticesCollider* goodLevelCollider = new VerticesCollider{ go2.get(), false, pLevelVertices };
	//go2->AddComponent(goodLevelCollider);



	////make new phy comp
	//PhysicsComponent* playerPhys = new PhysicsComponent{ go.get(), go->GetTransformComp(), playerCollider };



	////make ladder
	//std::vector<std::vector<Point2f>> ladderSVG;


	//SVGParser::GetVerticesFromSvgFile("../Data/LadderSVG.svg", ladderSVG);


	//std::vector<std::vector<Point2f>> ladderJumpOffPointsSVG;
	//SVGParser::GetVerticesFromSvgFile("../Data/LadderPointSVG.svg", ladderJumpOffPointsSVG);
	//


	//LadderComponent* ladderComp = new LadderComponent{ go2.get(), ladderSVG , ladderJumpOffPointsSVG };
	//go2->AddComponent(ladderComp);

	//CharacterComponent* myCharacter = new CharacterComponent{ go.get(),playerPhys, 5, goodLevelCollider, ladderComp };

	//go->AddComponent(myCharacter);
	//
	////make level



	//dae::InputManager& inputManager = dae::InputManager::GetInstance();


	////make horizontal controls
	//ControllerKey leftKey{ int(dae::ControllerButton::ArrowLeft), dae::ControllerButton::ArrowLeft };
	//std::shared_ptr<MoveCommand> moveleft = std::make_shared<MoveCommand>(myCharacter, -100.0f, 0.f);
	//inputManager.BindKey(leftKey, moveleft);

	//ControllerKey rightKey{ int(dae::ControllerButton::ArrowRight), dae::ControllerButton::ArrowRight };
	//std::shared_ptr<MoveCommand> moveRight = std::make_shared<MoveCommand>(myCharacter, 100.0f, 0.f);
	//inputManager.BindKey(rightKey, moveRight);

	////make vertical controls
	//ControllerKey upKey{ int(dae::ControllerButton::ArrowUp), dae::ControllerButton::ArrowUp };
	//std::shared_ptr<MoveCommand> moveUp = std::make_shared<MoveCommand>(myCharacter, 0.f, -100.f);
	//inputManager.BindKey(upKey, moveUp);

	//ControllerKey downKey{ int(dae::ControllerButton::ArrowDown), dae::ControllerButton::ArrowDown };
	//std::shared_ptr<MoveCommand> moveDown = std::make_shared<MoveCommand>(myCharacter, 0.0f, 100.f);
	//inputManager.BindKey(downKey, moveDown);

	//scene.Add(go2);

	//scene.Add(go);
	//

	////
	////float startPosGO3x = 200;
	////float startPosGO3y = 140;

	////make burgerparts
	//std::shared_ptr<GameObject> go3;

	//std::vector<std::vector<Point2f>> burgerPartPoints;
	//SVGParser::GetVerticesFromSvgFile("../Data/BurgerPartsSVG.svg", burgerPartPoints);

	//


	//for (size_t currentPart = 0; currentPart < burgerPartPoints.size(); ++currentPart)
	//{
	//	go3 = std::make_shared<GameObject>(burgerPartPoints.at(currentPart).at(0).x, burgerPartPoints.at(currentPart).at(0).y);

	//	RenderComponent* burgerRenderComponent = new RenderComponent{ go3.get() };

	//	burgerRenderComponent->SetTexture("Burger.png");
	//	go3->AddComponent(burgerRenderComponent);

	//	SDL_Point sizeBurger;
	//	auto burgerTexture = burgerRenderComponent->GetTexture()->GetSDLTexture();
	//	SDL_QueryTexture(burgerTexture, nullptr, nullptr, &sizeBurger.x, &sizeBurger.y);



	//	BurgerPartComponent* burgerPartComp = new BurgerPartComponent{ go3.get(), Point2f{burgerPartPoints.at(currentPart).at(0).x, burgerPartPoints.at(currentPart).at(0).y},
	//		float(sizeBurger.x), float(sizeBurger.y),myCharacter, goodLevelCollider , gameModeComponent };
	//	



	//	gameModeComponent->AddBurgerPart(burgerPartComp);

	//	go3->AddComponent(burgerPartComp);



	//	scene.Add(go3);

	//}
	//
	//float xPosEnemy = 228;
	//float yPosEnemy = 267;

	//std::shared_ptr<GameObject> goEnemy; 
	//goEnemy = std::make_shared<GameObject>(xPosEnemy, yPosEnemy);

	//RenderComponent* enemyRenderComponent = new RenderComponent{ goEnemy.get() };

	//enemyRenderComponent->SetTexture("Enemy.png");
	//goEnemy->AddComponent(enemyRenderComponent);

	//SDL_Point sizeEnemy;
	//auto enemyTexture = enemyRenderComponent->GetTexture()->GetSDLTexture();
	//SDL_QueryTexture(enemyTexture, nullptr, nullptr, &sizeEnemy.x, &sizeEnemy.y);

	//

	//Rectf* enemyCollider = new Rectf{ xPosEnemy, yPosEnemy, float(sizeEnemy.x), float(sizeEnemy.y) };

	//RectangleColliderComponent* enemyColliderComp = new RectangleColliderComponent{goEnemy.get(), false, enemyCollider };
	//PhysicsComponent* enemyPhysicsComp = new PhysicsComponent{ goEnemy.get(), goEnemy->GetTransformComp(), enemyColliderComp };
	//goEnemy->AddComponent(enemyPhysicsComp);

	//EnemyComponent* enemyComp = new EnemyComponent{ goEnemy.get(), enemyPhysicsComp,  goodLevelCollider, ladderComp , myCharacter };
	//goEnemy->AddComponent(enemyComp);


	//scene.Add(goEnemy);


	//scene.Add(gameModeGo);







	
	//scene.Add(go3);

}
