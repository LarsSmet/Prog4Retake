#include "pch.h"
#include "EnemyComponent.h"
#include <glm/gtx/norm.hpp>
#include <utils.cpp>
#include "GunComponent.h"
#include "ScoreComponent.h"



namespace dae
{

	EnemyComponent::EnemyComponent(GameObject* go, PhysicsComponent* physComp/*, PlayerComponent* playerComp*/) :
		BaseComponent{ go }, m_pPhysicsComponent{ physComp }, m_pTileMapComponent{nullptr}/*, m_pPlayerComponent{ playerComp }*/, m_HasDoneFirstUpdate{false},
		m_IsDying{false}

	{
		



		//m_pAIState = new MoveState(m_pPlayerComponent); 


	}

	

	EnemyComponent::~EnemyComponent()
	{
		delete m_pAIState;
		m_pAIState = nullptr;

	}

	void EnemyComponent::Update(float elapsedSec)
	{
		if (!m_HasDoneFirstUpdate)
		{
			OnFirstUpdate();
		}

		auto enemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		auto enemyRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();

		//offset needed to make sure it is in the cell, because sometimes the collision would make it so that it would be in another cell
		float offSet = 5;
		enemyPos.x += offSet;
		enemyPos.y += offSet;

		//std::cout << " x value: " << playerPos.x << " y value: " << playerPos.y;

		if (m_CurrentCell != m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y }))
		{
			//update cells arounnd rect
			m_pTileMapComponent->GetCellsAroundRect(enemyRectCol, m_CellsToCheck);
			m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });
		}
		else
		{
			//std::cout << " Can go left is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoLeft();
			//std::cout << /*" Can go right is: " <<*/ m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoRight();
			//std::cout << " Can go up is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoUp();
			//std::cout << " Can go down is: " << m_pTileMapComponent->GetCell(Point2f{playerPos.x, playerPos.y})->CanGoDown();
		}

		auto childGun = m_Owner->GetChildAt(0);//TODO: replace with actual child
		if (childGun != nullptr)
		{
			auto gunComp = childGun->GetComponent<GunComponent>();


			if (gunComp != nullptr)
			{
				//std::cout << "Guncomp found";
			//	gunComp->Shoot();
			}


			AIState* state = m_pAIState->Update(this, gunComp);




			//m_State->Update(this);
			if (state != nullptr)
			{
				delete m_pAIState;
				m_pAIState = state;
				state->OnEnter(this, gunComp);
			}

		}


		


		m_pPhysicsComponent->Update(elapsedSec);
			//HandleAI();
		


		for (size_t i = 0; i < m_CellsToCheck.size(); i++)
		{

			if (m_CellsToCheck[i]->HasCollision())
			{
				//handle collision
				m_pPhysicsComponent->HandleCollision(m_CellsToCheck[i]->GetRectCollider());



			}
		}


	



	}

	void EnemyComponent::OnFirstUpdate()
	{
		m_HasDoneFirstUpdate = true;

		m_pTileMapComponent = SceneManager::GetInstance().GetCurrentScene().GetTileMap()->GetComponent<TileMapComponent>();

		auto enemyPos = m_pPhysicsComponent->GetTransformComp()->GetPosition();
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });
		auto enemyrRectCol = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider();
		m_pTileMapComponent->GetCellsAroundRect(enemyrRectCol, m_CellsToCheck);
		m_CurrentCell = m_pTileMapComponent->GetCell(Point2f{ enemyPos.x, enemyPos.y });

		auto players = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("PLAYER");
		auto observers = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("OBSERVER");

		for (const auto& observer : observers)
		{
			auto observerComp = observer->GetComponent<ScoreComponent>();
			if (observerComp != nullptr)
			{
				m_Observers.emplace_back(observerComp);
			}

			
		}

		//TODO: Replace this with vec that takes closest player and change AI to use vec of GO instead of comp

		m_pPlayerComponent = players[0]->GetComponent<PlayerComponent>();

		m_pAIState = new MoveState(m_pPlayerComponent);

	}


	void EnemyComponent::HandleAI()
	{
		//Check raycast up, down, left right
		//go over all pos where no raycast hit

		//if no raycast, compare pos to best pos


		//positions to compare

		bool botHit = false;
		bool topHit = false;
		bool leftHit = false;
		bool rightHit = false;

		auto enemyWidth = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = m_pPhysicsComponent->GetColliderComponent()->GetRectCollider().height;

		glm::vec2 enemyCenter = GetEnemyCenter();

		glm::vec2 topPosToCompare{ enemyCenter.x, enemyCenter.y - enemyHeight/2 };
		glm::vec2 botPosToCompare{ enemyCenter.x, enemyCenter.y + enemyHeight/2 };
		glm::vec2 leftPosToCompare{ enemyCenter.x - enemyWidth / 2, enemyCenter.y };
		glm::vec2 rightPosToCompare{ enemyCenter.x + enemyWidth / 2, enemyCenter.y };
 


		for (size_t i = 0; i < m_CellsToCheck.size(); i++) //check the col for surrounding cells and store them if hit
		{
			if (m_CellsToCheck[i]->HasCollision())
			{

				auto hitInfo = m_pPhysicsComponent->GetColliderComponent()->OnCollision(m_CellsToCheck[i]->GetRectCollider());

				if (hitInfo.botColLeftIsHit || hitInfo.botColRightIsHit) 
				{
					botHit = true;
				}

				if (hitInfo.topColLeftIsHit || hitInfo.topColRightIsHit)
				{
					topHit = true;
				}

				if (hitInfo.leftColBotIsHit || hitInfo.leftColTopIsHit)
				{
					leftHit = true;
				}

				if (hitInfo.rightColBotIsHit || hitInfo.rightColTopIsHit)
				{
					rightHit = true;
				}
			

			}


		}

		
		float bestDistance = FLT_MAX;

		auto playerCenter = m_pPlayerComponent->GetPlayerCenter();
		Velocity newVelocity{};

		if (!topHit)
		{
			float distance = glm::distance2(topPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 0, -1};
			}
			
		}

		if (!botHit)
		{
			float distance = glm::distance2(botPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 0, 1 };
			}
		}

		if (!leftHit)
		{
			float distance = glm::distance2(leftPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ -1, 0 };
			}
		}


		if (!rightHit)
		{
			float distance = glm::distance2(rightPosToCompare, playerCenter);
			if (distance < bestDistance)
			{
				bestDistance = distance;
				newVelocity = Velocity{ 1, 0 };
			}
		}

		float speed = 30;

		newVelocity.x *= speed;
		newVelocity.y *= speed;

		SetVelocity(newVelocity);

	}





	//void EnemyComponent::HandleAI()
	//{
	//	// TODO: make get cellsize
	//	//get cells
	//	auto cellSize = m_CurrentCell->GetSize();
	//	//cellsize/2 offset to make sure it is in the center, so it always inside the cell, because sometimes it can cause some problems because of the collision

	//	//auto enemyPos = m_CurrentCell->GetPosition();

	//	Point2f pos{ m_pPhysicsComponent->GetTransformComp()->GetPosition().x + cellSize.x /2, 	m_pPhysicsComponent->GetTransformComp()->GetPosition().y + cellSize.y/2};

	//	auto enemyPos = m_pTileMapComponent->GetCell(pos)->GetPosition();


	//	

	//	Point2f POS{ m_pPhysicsComponent->GetTransformComp()->GetPosition().x, m_pPhysicsComponent->GetTransformComp()->GetPosition().y };


	//	auto leftTopCellPos = POS; //maybe change back to enemypos
	//	leftTopCellPos.x += (cellSize.x / 2);
	//	leftTopCellPos.y += (cellSize.y / 2);

	//	auto rightTopCellPos = enemyPos;
	//	rightTopCellPos.x += (cellSize.x / 2) + cellSize.x;
	//	rightTopCellPos.y += (cellSize.y / 2);

	//	auto leftBotCellPos = enemyPos;
	//	leftBotCellPos.x += (cellSize.x / 2);
	//	leftBotCellPos.y += cellSize.y + (cellSize.y / 2);

	//	auto rightBotCellPos = enemyPos;
	//	rightBotCellPos.x += (cellSize.x / 2) + cellSize.x;
	//	rightBotCellPos.y += cellSize.y + (cellSize.y / 2);

	//	auto leftTopcell = m_pTileMapComponent->GetCell(leftTopCellPos);
	//	auto rightTopCell = m_pTileMapComponent->GetCell(rightTopCellPos);
	//	auto leftBotCell = m_pTileMapComponent->GetCell(leftBotCellPos);
	//	auto rightBotCell = m_pTileMapComponent->GetCell(rightBotCellPos);

	//	//std::cout << " LeftBotcel :" << m_pTileMapComponent->GetCellIndex(leftBotCellPos) << " lefttopcell: "  << m_pTileMapComponent->GetCellIndex(leftTopCellPos);

	//	//std::cout << " posx : " << POS.x << " y pos : " << POS.y;

	//	auto playerPos = m_pPlayerComponent->GetPhysicsComp()->GetTransformComp()->GetPosition();

	//	glm::vec2 playerCenter{ playerPos.x + cellSize.x, playerPos.y + cellSize.y };

	//	glm::vec2 posToCompare{};


	//	float closestDistance = FLT_MAX;

	//	Velocity velocity{};

	//	std::string finalResult;



	//	bool yVelWasNegative;
	//	if (m_pPhysicsComponent->GetVelocity().y > 0)
	//	{
	//		yVelWasNegative = false;
	//	}
	//	else
	//	{
	//		yVelWasNegative = true;
	//	}

	//	bool xVelWasNegative;
	//	if (m_pPhysicsComponent->GetVelocity().x > 0)
	//	{
	//		xVelWasNegative = false;
	//	}
	//	else
	//	{
	//		xVelWasNegative = true;
	//	}


	//	// check dist when player moves 1 cell
	//	//check top cells
	//	if (leftTopcell->CanGoUp() && rightTopCell->CanGoUp()) //change current cell with lefttop cell
	//	{
	//		//left
	//		Point2f leftCellPos{ POS.x + 1, POS.y };
	//		Point2f leftOtherRayPoint{ leftCellPos.x, leftCellPos.y + cellSize.y};

	//		//check cell above
	//		float offset = 5;
	//		Point2f leftCellToCheck{ leftCellPos.x, leftCellPos.y - cellSize.y + offset };
	//		auto leftRectCol = m_pTileMapComponent->GetCell(leftCellToCheck)->GetRectCollider();


	//	//	std::cout << m_pTileMapComponent->GetCellIndex(leftCellToCheck);

	//		Point2f leftColLeftBot{ leftRectCol.left, leftRectCol.bottom };
	//		Point2f leftColRightBot{ leftRectCol.left + leftRectCol.width, leftRectCol.bottom };
	//		Point2f leftColRightTop{ leftRectCol.left + leftRectCol.width, leftRectCol.bottom + leftRectCol.height };
	//		Point2f leftColLeftTop{ leftRectCol.left, leftRectCol.bottom + leftRectCol.height };
	//		std::vector<Point2f> leftVerticesCol{ leftColLeftBot,leftColRightBot, leftColRightTop, leftColLeftTop };

	//		//right
	//		Point2f rightCellPos{ POS.x + 2* cellSize.x -1, POS.y };
	//		Point2f rightOtherRayPoint{ rightCellPos.x, rightCellPos.y + cellSize.y };

	//		//check cell above

	//	
	//		Point2f rightCellToCheck{ rightCellPos.x, rightCellPos.y - cellSize.y + offset };
	//		auto rightRectCol = m_pTileMapComponent->GetCell(rightCellToCheck)->GetRectCollider();


	//		//std::cout << m_pTileMapComponent->GetCellIndex(rightCellToCheck);

	//		Point2f rightColLeftBot{ rightRectCol.left, rightRectCol.bottom };
	//		Point2f rightColRightBot{ rightRectCol.left + rightRectCol.width, rightRectCol.bottom };
	//		Point2f rightColRightTop{ rightRectCol.left + rightRectCol.width, rightRectCol.bottom + rightRectCol.height };
	//		Point2f rightColLeftTop{ rightRectCol.left, rightRectCol.bottom + rightRectCol.height };
	//		std::vector<Point2f> rightVerticesCol{ rightColLeftBot,rightColRightBot, rightColRightTop, rightColLeftTop };

	//		utils::HitInfo hitInfo;
	//		utils::HitInfo hitInfo2;

	//		//if (utils::Raycast(leftVerticesCol, leftCellPos, leftOtherRayPoint, hitInfo) || utils::Raycast(rightVerticesCol, rightCellPos, rightOtherRayPoint, hitInfo2))
	//		//{

	//		//	//std::cout << " HIT TOP col ";
	//		//	////std::cout << " velocityx:  " << m_pPhysicsComponent->GetVelocity().x;
	//		//	//if (xVelWasNegative)
	//		//	//{
	//		//	//	velocity.x = -1;
	//		//	//	closestDistance = 0;
	//		//	//}
	//		//	//else
	//		//	//{
	//		//	//	velocity.x = 1;
	//		//	//	closestDistance = 0; //TODO: CHANGE CLOSESTDIST = 0 -> temporarily needed because it doesnt check the raycast of other sides
	//		//	//}
	//		//}
	//		//else
	//		//{

	//		//	std::cout << "why is this called";

	//			posToCompare.x = POS.x + cellSize.x;
	//			posToCompare.y = POS.y - cellSize.y;
	//			auto distance = glm::distance2(playerCenter, posToCompare);

	//			if (distance < closestDistance)
	//			{
	//				closestDistance = distance;
	//				velocity.x = 0;
	//				velocity.y = -1;
	//			//	std::cout << "TOP";
	//			}



	//		//}
	//	}

	//	//check bot cells
	//	if (leftBotCell->CanGoDown() && rightBotCell->CanGoDown())
	//	{
	//		////left
	//		Point2f leftCellPos{ POS.x + 1, POS.y + 2 * cellSize.y - 1 };
	//		Point2f leftOtherRayPoint{ leftCellPos.x, leftCellPos.y - cellSize.y };

	//		//check cell under
	//		float offset = 5;
	//		Point2f leftCellToCheck{ leftCellPos.x, leftCellPos.y + cellSize.y - offset }; 
	//		auto leftRectCol = m_pTileMapComponent->GetCell(leftCellToCheck)->GetRectCollider();


	//		//std::cout << m_pTileMapComponent->GetCellIndex(leftCellToCheck);

	//		Point2f leftColLeftBot{ leftRectCol.left, leftRectCol.bottom };
	//		Point2f leftColRightBot{ leftRectCol.left + leftRectCol.width, leftRectCol.bottom };
	//		Point2f leftColRightTop{ leftRectCol.left + leftRectCol.width, leftRectCol.bottom + leftRectCol.height };
	//		Point2f leftColLeftTop{ leftRectCol.left, leftRectCol.bottom + leftRectCol.height };
	//		std::vector<Point2f> leftVerticesCol{ leftColLeftBot,leftColRightBot, leftColRightTop, leftColLeftTop };

	//		////right
	//		Point2f rightCellPos{ POS.x + 2 * cellSize.x -1, POS.y + 2 * cellSize.y - 1 };
	//		Point2f rightOtherRayPoint{ rightCellPos.x, leftCellPos.y - cellSize.y };

	//		//check cell under
	//		Point2f rightCellToCheck{ rightCellPos.x, leftCellPos.y + cellSize.y - offset  }; 
	//		auto rightRectCol = m_pTileMapComponent->GetCell(rightCellToCheck)->GetRectCollider();


	//		//std::cout << m_pTileMapComponent->GetCellIndex(rightCellToCheck);

	//		Point2f rightColLeftBot{ rightRectCol.left, rightRectCol.bottom };
	//		Point2f rightColRightBot{ rightRectCol.left + rightRectCol.width, rightRectCol.bottom };
	//		Point2f rightColRightTop{ rightRectCol.left + rightRectCol.width, rightRectCol.bottom + rightRectCol.height };
	//		Point2f rightColLeftTop{ rightRectCol.left, rightRectCol.bottom + rightRectCol.height };
	//		std::vector<Point2f> rightVerticesCol{ rightColLeftBot,rightColRightBot, rightColRightTop, rightColLeftTop };

	//		utils::HitInfo hitInfo;
	//		utils::HitInfo hitInfo2;

	//		//if (utils::Raycast(leftVerticesCol, leftCellPos, leftOtherRayPoint, hitInfo) || utils::Raycast(rightVerticesCol, rightCellPos, rightOtherRayPoint, hitInfo2))
	//		//{

	//		///*	if (xVelWasNegative)
	//		//	{
	//		//		velocity.x = -1;
	//		//		closestDistance = 0;
	//		//	}
	//		//	else
	//		//	{
	//		//		velocity.x = 1;
	//		//		closestDistance = 0;
	//		//	}*/
	//		//}
	//		//else
	//		//{


	//			posToCompare.x = POS.x + cellSize.x;
	//			posToCompare.y = POS.y + (3 * cellSize.y);
	//			auto distance = glm::distance2(playerCenter, posToCompare);


	//			if (distance < closestDistance)
	//			{
	//				closestDistance = distance;
	//				velocity.x = 0;
	//				velocity.y = 1;
	//				//std::cout << "BOT";
	//			}

	//		//}
	//		
	//	}

	//	//check left cells

	//	if (leftTopcell->CanGoLeft() && leftBotCell->CanGoLeft())
	//	{

	//		//top
	//		Point2f topCellPos{ POS.x + 1, POS.y };
	//		Point2f topOtherRayPoint{ topCellPos.x + cellSize.x, topCellPos.y };

	//		//check cell to right
	//		Point2f topCellToCheck{ topCellPos.x - cellSize.x, topCellPos.y };
	//		auto topRectCol = m_pTileMapComponent->GetCell(topCellToCheck)->GetRectCollider();

	//		Point2f topColLeftBot{ topRectCol.left, topRectCol.bottom };
	//		Point2f topColRightBot{ topRectCol.left + topRectCol.width, topRectCol.bottom };
	//		Point2f topColRightTop{ topRectCol.left + topRectCol.width, topRectCol.bottom + topRectCol.height };
	//		Point2f topColLeftTop{ topRectCol.left, topRectCol.bottom + topRectCol.height };
	//		std::vector<Point2f> topVerticesCol{ topColLeftBot,topColRightBot,topColRightTop, topColLeftTop };

	//		//bot
	//		Point2f botCellPos{ POS.x + 1, POS.y + 2 * cellSize.y - 1 };
	//		Point2f botOtherRayPoint{ botCellPos.x + cellSize.x, botCellPos.y };

	//		//check cell to right
	//		Point2f botCellToCheck{ botCellPos.x - cellSize.x, botCellPos.y };
	//		auto botRectCol = m_pTileMapComponent->GetCell(botCellToCheck)->GetRectCollider();

	//		Point2f botColLeftBot{ botRectCol.left, botRectCol.bottom };
	//		Point2f botColRightBot{ botRectCol.left + botRectCol.width, botRectCol.bottom };
	//		Point2f botColRightTop{ botRectCol.left + botRectCol.width, botRectCol.bottom + botRectCol.height };
	//		Point2f botColLeftTop{ botRectCol.left, botRectCol.bottom + botRectCol.height };
	//		std::vector<Point2f> botVerticesCol{ botColLeftBot, botColRightBot,botColRightTop, botColLeftTop };

	//		utils::HitInfo hitInfo;
	//		utils::HitInfo hitInfo2;

	//	//	if (utils::Raycast(topVerticesCol, topCellPos, topOtherRayPoint, hitInfo) || utils::Raycast(botVerticesCol, botCellPos, botOtherRayPoint, hitInfo2))
	//	//	{
	//	///*		if (yVelWasNegative)
	//	//		{
	//	//			velocity.y = -1;
	//	//			closestDistance = 0;
	//	//		}
	//	//		else
	//	//		{
	//	//			velocity.y = 1;
	//	//			closestDistance = 0;
	//	//		}*/
	//	//	}
	//	//	else
	//	//	{




	//			posToCompare.x = POS.x - cellSize.x;
	//			posToCompare.y = POS.y + cellSize.y;
	//			auto distance = glm::distance2(playerCenter, posToCompare);

	//			if (distance < closestDistance)
	//			{
	//				closestDistance = distance;
	//				velocity.x = -1;
	//				velocity.y = 0;
	//			//	std::cout << "LEFT";
	//			}

	//		//}
	//	}



	//	//check right cells
	//	if (rightTopCell->CanGoRight() && rightBotCell->CanGoRight())
	//	{

	//		//std::cout << "is this called after bot?";
	//		
	//		//Point2f otherTopRayPoint{ POS.x + 2 * cellSize.x +1 , POS.y };
	//		
	//		//top
	//		Point2f topCellPos{ POS.x + cellSize.x, POS.y };
	//		Point2f topOtherRayPoint{ topCellPos.x  + cellSize.x + 1 , topCellPos.y };

	//		//check cell to right
	//		Point2f topCellToCheck{ topCellPos.x +  cellSize.x, topCellPos.y };
	//		auto topRectCol = m_pTileMapComponent->GetCell(topCellToCheck)->GetRectCollider();

	//		Point2f topColLeftBot{ topRectCol.left, topRectCol.bottom };
	//		Point2f topColRightBot{ topRectCol.left + topRectCol.width, topRectCol.bottom };
	//		Point2f topColRightTop{ topRectCol.left + topRectCol.width, topRectCol.bottom + topRectCol.height };
	//		Point2f topColLeftTop{ topRectCol.left, topRectCol.bottom + topRectCol.height };
	//		std::vector<Point2f> topVerticesCol{ topColLeftBot,topColRightBot,topColRightTop, topColLeftTop };

	//		//bot
	//		Point2f botCellPos{ POS.x + cellSize.x, POS.y + 2 * cellSize.y - 1 };
	//		Point2f botOtherRayPoint{ botCellPos.x + cellSize.x + 1, botCellPos.y };
	//		
	//		//check cell to right
	//		Point2f botCellToCheck{ botCellPos.x + cellSize.x, botCellPos.y };
	//		auto botRectCol = m_pTileMapComponent->GetCell(botCellToCheck)->GetRectCollider();

	//		Point2f botColLeftBot{ botRectCol.left, botRectCol.bottom };
	//		Point2f botColRightBot{ botRectCol.left + botRectCol.width, botRectCol.bottom };
	//		Point2f botColRightTop{ botRectCol.left + botRectCol.width, botRectCol.bottom + botRectCol.height };
	//		Point2f botColLeftTop{ botRectCol.left, botRectCol.bottom + botRectCol.height };
	//		std::vector<Point2f> botVerticesCol{ botColLeftBot, botColRightBot,botColRightTop, botColLeftTop };

	//		utils::HitInfo hitInfo;
	//		utils::HitInfo hitInfo2;

	//	//	if (utils::Raycast(topVerticesCol, topCellPos, topOtherRayPoint, hitInfo) || utils::Raycast(botVerticesCol, botCellPos, botOtherRayPoint, hitInfo2))
	//	//	{
	//	///*		if (yVelWasNegative)
	//	//		{
	//	//			velocity.y = -1;
	//	//			closestDistance = 0;
	//	//		}
	//	//		else
	//	//		{
	//	//			closestDistance = 0;
	//	//			velocity.y = 1;
	//	//		}*/

	//	//		//std::cout << "is this the problem";

	//	//	}
	//	//	else
	//	//	{
	//	
	//		//	if (!m_pTileMapComponent->GetCell(cellToCheck)->HasCollision())
	//			//{
	//				posToCompare.x = POS.x + (3 * cellSize.x);
	//				posToCompare.y = POS.y + cellSize.y;
	//				auto distance = glm::distance2(playerCenter, posToCompare);

	//				if (distance <= closestDistance)
	//				{
	//					closestDistance = distance;
	//					velocity.x = 1;
	//					velocity.y = 0;
	//					//std::cout << "RIGHT";
	//				}

	//			//}
	//		//}
	//	}

	//	float speed =30.0f;



	//	//std::cout << " VelocityX : " << velocity.x << " velocityy Y: " << velocity.y;

	//	velocity.x *= speed;
	//	velocity.y *= speed;
	//	//std::cout << " Final result is: " << finalResult;
	//	m_pPhysicsComponent->SetVelocity(velocity);
	//}

	void EnemyComponent::SetVelocity(Velocity newVelocity)
	{
		m_pPhysicsComponent->SetVelocity(newVelocity);
		m_Velocity = newVelocity;
		
	}

	PhysicsComponent* EnemyComponent::GetPhysicsComp()
	{
		
			return m_pPhysicsComponent;
		
	}

	glm::vec2 EnemyComponent::GetEnemyCenter()
	{
		auto enemyPhysComp = GetPhysicsComp();
		auto enemyPos = enemyPhysComp->GetTransformComp()->GetPosition();
		auto enemyWidth = enemyPhysComp->GetColliderComponent()->GetRectCollider().width;
		auto enemyHeight = enemyPhysComp->GetColliderComponent()->GetRectCollider().height;
		return { enemyPos.x + enemyWidth / 2, enemyPos.y + enemyHeight / 2 };
	}

	void EnemyComponent::Kill()
	{
		Notify(Event::BlueTankdied);

		auto bullets = SceneManager::GetInstance().GetCurrentScene().GetObjectsOfTag("BULLET");

		for (const auto& bullet : bullets)
		{
			auto bulletComp = bullet->GetComponent<BulletComponent>();

			if (bulletComp != nullptr)
			{
				bulletComp->SetEnemiesAreChecked(false);
			}
		}

		m_Observers.clear();
		m_Owner->Destroy();
	}

}
