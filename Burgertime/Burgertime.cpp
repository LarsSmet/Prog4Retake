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
#include "ScoreComponent.h"


using namespace dae;
void LoadGame();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();

	//main menu scene
	//run
	//create gamemodescene after selection

	LoadGame();

	engine.Run();



	return 0;



}



void SpawnEnemyPrefab()
{
	//if scene 1 -> spawn at that pos
	//if scene 2 -> spawn at that pos
	//if scene 3 -> spawn at that pos


	float enemyStartX = 16;
	float enemyStartY = 232; //250
	auto enemy = std::make_shared<GameObject>(enemyStartX, enemyStartY, "ENEMY");
	RenderComponent* renderComponent = new RenderComponent{ enemy.get() , false,nullptr }; //maybe change to true if we want the player to rotate
	renderComponent->SetTexture("Tank.png");
	enemy->AddComponent(renderComponent);
	auto texture = renderComponent->GetTexture()->GetSDLTexture();
	SDL_Point enemySize;
	SDL_QueryTexture(texture, nullptr, nullptr, &enemySize.x, &enemySize.y);
	Rectf enemyShape{ enemyStartX,enemyStartY + float(enemySize.y), float(enemySize.x),float(enemySize.y) }; //IMPORTANT! ypos needs to be + SIZE because of rect and render having dif starting points
	RectColliderComponent* enemyCollider = new RectColliderComponent{ enemy.get(), enemyShape };
	PhysicsComponent* myEnemyPhysicsComp = new PhysicsComponent{ enemy.get(), enemy->GetTransformComp(), enemyCollider };
	enemy->AddComponent(myEnemyPhysicsComp);
	EnemyComponent* myEnemyComp = new EnemyComponent{ enemy.get(), myEnemyPhysicsComp };
	
	enemy->AddComponent(myEnemyComp);

	//create enemygun
	float xOffSetEnemyGun = 10.0f;
	float yOffSetEnemyGun = -3.0f;
	float enemyGunStartX = enemyStartX + xOffSetEnemyGun;
	float enemyGunStartY = enemyStartY + yOffSetEnemyGun;
	auto enemyGun = std::make_shared<GameObject>(enemyGunStartX, enemyGunStartY, "ENEMYGUN");
	SDL_Point* sdlEnemyGunPoint = new SDL_Point{ 0,0 };
	renderComponent = new RenderComponent{ enemyGun.get() , true, sdlEnemyGunPoint };
	renderComponent->SetTexture("Gun.png");
	enemyGun->AddComponent(renderComponent);
	GunComponent* myEnemyGunComponent = new GunComponent{ enemyGun.get(), nullptr, myEnemyComp };
	enemyGun->AddComponent(myEnemyGunComponent);

	enemyGun->SetParent(enemy);

	auto& scene = SceneManager::GetInstance().GetCurrentScene();

	scene.Add(enemy);
	scene.Add(enemyGun);



}


void CreateScene(const std::shared_ptr<GameObject>& player, const std::shared_ptr<GameObject>& gun, const std::shared_ptr<GameObject>& score)
{


	auto& scene = SceneManager::GetInstance().CreateScene("Demo");



	//create tilemap
	float tileMapStartX = 0;
	float tilemapStartY = 200;
	auto go = std::make_shared<GameObject>(tileMapStartX, tilemapStartY, "TILEMAP");
	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/Level0.txt" };
	tileMapComponent->ConvertFileToMap();
	go->AddComponent(tileMapComponent);
	scene.Add(go);
	scene.AddTileMap(go);

	SpawnEnemyPrefab();




	scene.Add(player); 
	scene.Add(gun);
	scene.Add(score);
	scene.AddPrefabToReload(SpawnEnemyPrefab);

	//EntityManager& entityManager = EntityManager::GetInstance();

	//entityManager.AddPlayer(player);
	//entityManager.AddEnemy(enemy);

}


void CreateScene1(const std::shared_ptr<GameObject>& player, const std::shared_ptr<GameObject>& gun, const std::shared_ptr<GameObject>& score)
{


	auto& scene = SceneManager::GetInstance().CreateScene("Demo");



	//create tilemap
	float tileMapStartX = 0;
	float tilemapStartY = 200;
	auto go = std::make_shared<GameObject>(tileMapStartX, tilemapStartY, "TILEMAP");
	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/Level1.txt" };
	tileMapComponent->ConvertFileToMap();
	go->AddComponent(tileMapComponent);
	scene.Add(go);
	scene.AddTileMap(go);




	scene.Add(player);
	scene.Add(gun);

	scene.Add(score);

	scene.AddPrefabToReload(SpawnEnemyPrefab);
}

void CreateScene2(const std::shared_ptr<GameObject>& player, const std::shared_ptr<GameObject>& gun, const std::shared_ptr<GameObject>& score)
{


	auto& scene = SceneManager::GetInstance().CreateScene("Demo");



	//create tilemap
	float tileMapStartX = 0;
	float tilemapStartY = 200;
	auto go = std::make_shared<GameObject>(tileMapStartX, tilemapStartY, "TILEMAP");
	TileMapComponent* tileMapComponent = new TileMapComponent{ go.get(), "../Data/Level2.txt" };
	tileMapComponent->ConvertFileToMap();
	go->AddComponent(tileMapComponent);
	scene.Add(go);
	scene.AddTileMap(go);




	scene.Add(player);
	scene.Add(gun);

	scene.Add(score);

	scene.AddPrefabToReload(SpawnEnemyPrefab);
}


void LoadGame()
{
	

	//create player
	float playerStartX = 50;
	float playerStartY = 450; //250
	auto player = std::make_shared<GameObject>(playerStartX, playerStartY, "PLAYER");
	RenderComponent* renderComponent = new RenderComponent{ player.get() , false,nullptr }; //maybe change to true if we want the player to rotate
	renderComponent->SetTexture("Tank.png");
	player->AddComponent(renderComponent);
	auto texture = renderComponent->GetTexture()->GetSDLTexture();
	SDL_Point size;
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	Rectf playerShape{ playerStartX,playerStartY + float(size.y), float(size.x),float(size.y) }; //IMPORTANT! ypos needs to be + SIZE because of rect and render having dif starting points
	RectColliderComponent* playerCollider = new RectColliderComponent{ player.get(), playerShape };
	PhysicsComponent* myPlayerPhysicsComp = new PhysicsComponent{ player.get(), player->GetTransformComp(), playerCollider };
	player->AddComponent(myPlayerPhysicsComp);
	PlayerComponent* myPlayerComp = new PlayerComponent{ player.get(), myPlayerPhysicsComp };
	player->AddComponent(myPlayerComp);
	//create gun
	float xOffSetGun = 10.0f;
	float yOffSetGun = -3.0f;
	float gunStartX = playerStartX + xOffSetGun;
	float gunStartY = playerStartY + yOffSetGun;
	auto gun = std::make_shared<GameObject>(gunStartX, gunStartY, "PLAYERGUN");
	SDL_Point* sdlGunPoint = new SDL_Point{ 0,0 };
	renderComponent = new RenderComponent{ gun.get() , true, sdlGunPoint };
	renderComponent->SetTexture("Gun.png");
	gun->AddComponent(renderComponent);
	GunComponent* myGunComponent = new GunComponent{ gun.get(), myPlayerComp, nullptr};
	gun->AddComponent(myGunComponent);

	gun->SetParent(player);


	float scoreTrackerX = 140;
	float scoreTrackerY = 20;
	auto scoreTracker = std::make_shared<GameObject>(scoreTrackerX, scoreTrackerY, "OBSERVER");

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	std::string text = "Score: ";
	renderComponent = new RenderComponent{ scoreTracker.get() , false, nullptr };

	SDL_Color white{ 255,255,255 };
	TextComponent* textComp = new TextComponent{scoreTracker.get(), text, font, renderComponent, white };
	ScoreComponent* scoreComp = new ScoreComponent{ scoreTracker.get(), textComp };


	scoreTracker->AddComponent(renderComponent);
	//scoreTracker->AddComponent(textComp);
	scoreTracker->AddComponent(scoreComp);


	//commands
	dae::InputManager& inputManager = dae::InputManager::GetInstance();
	//make horizontal controls
	ControllerAction leftControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowLeft,0 };
	std::shared_ptr<MoveCommand> moveleft = std::make_shared<MoveCommand>(myPlayerComp, -50.0f, 0.f);
	inputManager.BindKey(leftControllerButton, moveleft);

	ControllerAction rightControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowRight,0 };
	std::shared_ptr<MoveCommand> moveRight = std::make_shared<MoveCommand>(myPlayerComp, 50.0f, 0.f);
	inputManager.BindKey(rightControllerButton, moveRight);

	//make vertical controls
	ControllerAction upControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowUp,0 };
	std::shared_ptr<MoveCommand> moveUp = std::make_shared<MoveCommand>(myPlayerComp, 0.f, -50.f);
	inputManager.BindKey(upControllerButton, moveUp);

	ControllerAction downControllerButton{ ActionState::Hold, dae::ControllerButton::ArrowDown,0 };
	std::shared_ptr<MoveCommand> moveDown = std::make_shared<MoveCommand>(myPlayerComp, 0.0f, 50.f);
	inputManager.BindKey(downControllerButton, moveDown);

	//gun commands
	ControllerAction shootControllerButton{ ActionState::Down, dae::ControllerButton::ButtonX,0 };
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>(myGunComponent);
	inputManager.BindKey(shootControllerButton, shoot);

	ControllerAction rotateGunControllerButton{ ActionState::Hold, dae::ControllerButton::ButtonB,0 };
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



	CreateScene(player, gun, scoreTracker);
	CreateScene1(player, gun, scoreTracker);
	CreateScene2(player, gun, scoreTracker);




}