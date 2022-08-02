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
//#include <PhysicsComponent.h>
//#include "CharacterComponent.h"
#include "Texture2D.h"
//#include <VerticesCollider.h>
#include <SVGParser.cpp>
#include <TileMapComponent.h>
#include "PlayerComponent.h"
#include "GameCommands.h"
#include "GunComponent.h"
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



	

	

	//create tilemap
	float tileMapStartX = 0;
	float tilemapStartY = 200;
	auto go = std::make_shared<GameObject>(tileMapStartX, tilemapStartY);
	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/TileMap2.txt" };
	tileMapComponent->ConvertFileToMap();
	go->AddComponent(tileMapComponent);
	scene.Add(go);

	//create player
	float playerStartX = 50;
	float playerStartY = 250;
	auto player = std::make_shared<GameObject>(playerStartX, playerStartY);
	RenderComponent* renderComponent = new RenderComponent{ player.get() , false,nullptr}; //maybe change to true if we want the player to rotate
	renderComponent->SetTexture("Tank.png");
	player->AddComponent(renderComponent);
	auto texture = renderComponent->GetTexture()->GetSDLTexture();
	SDL_Point size;
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	Rectf playerShape{ playerStartX,playerStartY + float(size.y), float(size.x),float(size.y) }; //IMPORTANT! ypos needs to be + SIZE because of rect and render having dif starting points
	RectColliderComponent* playerCollider = new RectColliderComponent{ player.get(), playerShape };
	PhysicsComponent* myPlayerPhysicsComp = new PhysicsComponent{ player.get(), player->GetTransformComp(), playerCollider };
	player->AddComponent(myPlayerPhysicsComp);
	PlayerComponent* myPlayerComp = new PlayerComponent{ player.get(), myPlayerPhysicsComp , tileMapComponent};
	player->AddComponent(myPlayerComp);
	//create gun
	float xOffSetGun = 10.0f;
	float yOffSetGun = -3.0f;
	float gunStartX = playerStartX + xOffSetGun;
	float gunStartY = playerStartY + yOffSetGun;
	auto gun = std::make_shared<GameObject>(gunStartX, gunStartY);
	SDL_Point* sdlPoint = new SDL_Point{0,0};
	renderComponent = new RenderComponent{ gun.get() , true, sdlPoint};
	renderComponent->SetTexture("Gun.png");
	gun->AddComponent(renderComponent);
	GunComponent* myGunComponent = new GunComponent{ gun.get(), myPlayerComp, scene };
	gun->AddComponent(myGunComponent);




	//commands
	dae::InputManager& inputManager = dae::InputManager::GetInstance();
	//make horizontal controls
	ControllerKey leftKey{ int(dae::ControllerButton::ArrowLeft), dae::ControllerButton::ArrowLeft };
	std::shared_ptr<MoveCommand> moveleft = std::make_shared<MoveCommand>(myPlayerComp, -50.0f, 0.f);
	inputManager.BindKey(leftKey, moveleft);

	ControllerKey rightKey{ int(dae::ControllerButton::ArrowRight), dae::ControllerButton::ArrowRight };
	std::shared_ptr<MoveCommand> moveRight = std::make_shared<MoveCommand>(myPlayerComp, 50.0f, 0.f);
	inputManager.BindKey(rightKey, moveRight);

	//make vertical controls
	ControllerKey upKey{ int(dae::ControllerButton::ArrowUp), dae::ControllerButton::ArrowUp };
	std::shared_ptr<MoveCommand> moveUp = std::make_shared<MoveCommand>(myPlayerComp, 0.f, -50.f);
	inputManager.BindKey(upKey, moveUp);

	ControllerKey downKey{ int(dae::ControllerButton::ArrowDown), dae::ControllerButton::ArrowDown };
	std::shared_ptr<MoveCommand> moveDown = std::make_shared<MoveCommand>(myPlayerComp, 0.0f, 50.f);
	inputManager.BindKey(downKey, moveDown);

	//gun command
	ControllerKey shootKey{ int(dae::ControllerButton::ButtonX), dae::ControllerButton::ButtonX };
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>(myGunComponent);
	inputManager.BindKey(shootKey, shoot);
	scene.Add(player);
	scene.Add(gun);

	
}
