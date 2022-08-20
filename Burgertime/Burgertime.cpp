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

#include <TileMapComponent.h>
#include "PlayerComponent.h"
#include "GameCommands.h"
#include "GunComponent.h"
#include "EnemyComponent.h"
//#include "GameCommands.h"
//#include "BurgerPartComponent.h"
//#include "GameMode.h"
//#include "GameMode.h"
//#include "EnemyComponent.h"
#include "EntityManager.h"


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
	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/TileMap3.txt" };
	tileMapComponent->ConvertFileToMap();
	go->AddComponent(tileMapComponent);
	scene.Add(go);

	//create player
	float playerStartX = 50;
	float playerStartY = 450; //250
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
	SDL_Point* sdlGunPoint = new SDL_Point{0,0};
	renderComponent = new RenderComponent{ gun.get() , true, sdlGunPoint};
	renderComponent->SetTexture("Gun.png");
	gun->AddComponent(renderComponent);
	GunComponent* myGunComponent = new GunComponent{ gun.get(), myPlayerComp, nullptr, scene, tileMapComponent };
	gun->AddComponent(myGunComponent);

	


	//commands
	dae::InputManager& inputManager = dae::InputManager::GetInstance();
	//make horizontal controls
	ControllerAction leftControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowLeft };
	std::shared_ptr<MoveCommand> moveleft = std::make_shared<MoveCommand>(myPlayerComp, -50.0f, 0.f);
	inputManager.BindKey(leftControllerButton, moveleft);

	ControllerAction rightControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowRight };
	std::shared_ptr<MoveCommand> moveRight = std::make_shared<MoveCommand>(myPlayerComp, 50.0f, 0.f);
	inputManager.BindKey(rightControllerButton, moveRight);

	//make vertical controls
	ControllerAction upControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowUp };
	std::shared_ptr<MoveCommand> moveUp = std::make_shared<MoveCommand>(myPlayerComp, 0.f, -50.f);
	inputManager.BindKey(upControllerButton, moveUp);

	ControllerAction downControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowDown };
	std::shared_ptr<MoveCommand> moveDown = std::make_shared<MoveCommand>(myPlayerComp, 0.0f, 50.f);
	inputManager.BindKey(downControllerButton, moveDown);

	//gun commands
	ControllerAction shootControllerButton{ ActionState::Down, dae::ControllerButton::ButtonX };
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>(myGunComponent);
	inputManager.BindKey(shootControllerButton, shoot);

	ControllerAction rotateGunControllerButton{ ActionState::Hold, dae::ControllerButton::ButtonB };
	std::shared_ptr<RotateGunCommand> rotate = std::make_shared<RotateGunCommand>(myGunComponent);
	inputManager.BindKey(rotateGunControllerButton, rotate);


	//KEYBOARD

	//make horizontal controls
	KeyBoardAction leftKeyKeyBoard{ ActionState::Down, SDL_SCANCODE_LEFT };
	inputManager.BindKey(leftKeyKeyBoard, moveleft);

	
	KeyBoardAction rightKeyKeyBoard{ ActionState::Down, SDL_SCANCODE_RIGHT };
	inputManager.BindKey(rightKeyKeyBoard, moveRight);

	//make vertical controls
	KeyBoardAction upKeyKeyBoard{ ActionState::Down, SDL_SCANCODE_UP };
	inputManager.BindKey(upKeyKeyBoard, moveUp);

	
	KeyBoardAction downKeyKeyBoard{ ActionState::Down, SDL_SCANCODE_DOWN };
	inputManager.BindKey(downKeyKeyBoard, moveDown);

	//gun command
	KeyBoardAction shootKeyKeyBoard{ ActionState::Down, SDL_SCANCODE_S };
	inputManager.BindKey(shootKeyKeyBoard, shoot);

	KeyBoardAction rotateGunKeyKeyBoard{ ActionState::Hold, SDL_SCANCODE_R };
	inputManager.BindKey(rotateGunKeyKeyBoard, rotate);

	float enemyStartX = 16;
	float enemyStartY = 232; //250
	auto enemy = std::make_shared<GameObject>(enemyStartX, enemyStartY);
	renderComponent = new RenderComponent{ enemy.get() , false,nullptr }; //maybe change to true if we want the player to rotate
	renderComponent->SetTexture("Tank.png");
	enemy->AddComponent(renderComponent);
	texture = renderComponent->GetTexture()->GetSDLTexture();
	SDL_Point enemySize;
	SDL_QueryTexture(texture, nullptr, nullptr, &enemySize.x, &enemySize.y);
	Rectf enemyShape{ enemyStartX,enemyStartY + float(enemySize.y), float(enemySize.x),float(enemySize.y) }; //IMPORTANT! ypos needs to be + SIZE because of rect and render having dif starting points
	RectColliderComponent* enemyCollider = new RectColliderComponent{ enemy.get(), enemyShape };
	PhysicsComponent* myEnemyPhysicsComp = new PhysicsComponent{ enemy.get(), enemy->GetTransformComp(), enemyCollider };
	enemy->AddComponent(myEnemyPhysicsComp);
	EnemyComponent* myEnemyComp = new EnemyComponent{ enemy.get(), myEnemyPhysicsComp , tileMapComponent, myPlayerComp };
	enemy->AddComponent(myEnemyComp);

	//create enemygun
	float xOffSetEnemyGun = 10.0f;
	float yOffSetEnemyGun = -3.0f;
	float enemyGunStartX = enemyStartX + xOffSetEnemyGun;
	float enemyGunStartY = enemyStartY + yOffSetEnemyGun;
	auto enemyGun = std::make_shared<GameObject>(enemyGunStartX, enemyGunStartY);
	SDL_Point* sdlEnemyGunPoint = new SDL_Point{ 0,0 };
	renderComponent = new RenderComponent{ enemyGun.get() , true, sdlEnemyGunPoint };
	renderComponent->SetTexture("Gun.png");
	enemyGun->AddComponent(renderComponent);
	GunComponent* myEnemyGunComponent = new GunComponent{ enemyGun.get(),  nullptr, myEnemyComp, scene, tileMapComponent };
	enemyGun->AddComponent(myEnemyGunComponent);

	enemy->AddChild(enemyGun);

	scene.Add(player);
	scene.Add(gun);
	scene.Add(enemy);
	scene.Add(enemyGun);

	EntityManager& entityManager = EntityManager::GetInstance();

	entityManager.AddPlayer(player);
	entityManager.AddEnemy(enemy);

	
}
