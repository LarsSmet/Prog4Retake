#include "MiniginPCH.h"
#include "TileMapComponent.h"
#include <fstream>
#include"ResourceManager.h"
#include "GameObject.h"

namespace dae
{
	TileMapComponent::TileMapComponent(GameObject* go, const char* filename): BaseComponent{go}, m_File{filename}, m_Go{go}
	{
		//ConvertFileToMap();
	}

	TileMapComponent::~TileMapComponent()
	{

		//delete m_File;
		//m_File = nullptr;

	}



	//void TileMapComponent::ConvertFileToMap()
	//{


	//	ResourceManager::GetInstance().Init("../Data/");

	//	size_t amountOfCol;
	//	size_t amountOfRows;

	//	float cellWidth;
	//	float cellHeight;

	//	int value;

	//	auto transformCompPos = m_Go->GetTransformComp()->GetPosition();
	//	
	//	glm::vec2 position{ transformCompPos.x, transformCompPos.y}; //change to transform component later

	//	std::ifstream input(m_File);

	//	if (!input.is_open())
	//	{
	//		std::cout << "Opening file failed";
	//		return;
	//	}

	//	//first value read is the amount of col, second value is the amount of rows
	//	//third value is the cell width, fourth value is the cell height
	//	input >> amountOfCol;
	//	input >> amountOfRows;
	//	input >> cellWidth;
	//	input >> cellHeight;


	//	//create nested for loops to intialize each cell

	//	for (size_t row = 0; row < amountOfRows; ++row)
	//	{
	//		for (size_t col = 0; col < amountOfCol; ++col)
	//		{
	//			//set size
	//			m_CellToAdd.SetSize(cellWidth, cellHeight);
	//			
	//			//set pos

	//			float xPos = (col * cellWidth) + position.x;
	//			float yPos = (row * cellHeight) + position.y ;

	//			m_CellToAdd.SetPos(xPos,yPos) ;


	//			//get input for col
	//			input >> value;


	//			//std::cout << value;

	//			if (value == 0)
	//			{
	//				//set col is false
	//				m_CellToAdd.SetCollision(false);
	//			}
	//			else if (value == 1)
	//			{
	//				//set col to true
	//				//rectCollider = new Rectf{ xPos, yPos, cellWidth, cellHeight };
	//				//colliderComp = new RectColliderComponent{ m_Go, rectCollider };
	//				//cellToAdd.SetCollision(true, new RectColliderComponent{ m_Go, new Rectf{ xPos, yPos, cellWidth, cellHeight } });
	//		
	//				m_CellToAdd.SetCollision(true,  RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
	//			
	//			}

	//			//get input for texture
	//			input >> value;
	//			//std::cout << value;

	//			switch (value)
	//			{
	//			case 2:
	//				//set to road
	//				m_CellToAdd.SetTexture("RoadTile.png");
	//				break;
	//			case 3:
	//				//set to wall
	//				m_CellToAdd.SetTexture("WallTile.png");
	//				break;
	//			}

	//			
	//			
	//			//std::cout << "emplace";
	//			m_Map.emplace_back(m_CellToAdd);


	//		


	//		}
	//	}

	//	input.close();

	//}


	void TileMapComponent::ConvertFileToMap()
	{


		ResourceManager::GetInstance().Init("../Data/");

		size_t amountOfCol;
		size_t amountOfRows;

		float cellWidth;
		float cellHeight;

		int value;

		auto transformCompPos = m_Go->GetTransformComp()->GetPosition();

		glm::vec2 position{ transformCompPos.x, transformCompPos.y }; //change to transform component later

		std::ifstream input(m_File);

		if (!input.is_open())
		{
			std::cout << "Opening file failed";
			return;
		}

		//first value read is the amount of col, second value is the amount of rows
		//third value is the cell width, fourth value is the cell height
		input >> amountOfCol;
		input >> amountOfRows;
		input >> cellWidth;
		input >> cellHeight;


		//create nested for loops to intialize each cell

		for (size_t row = 0; row < amountOfRows; ++row)
		{
			for (size_t col = 0; col < amountOfCol; ++col)
			{
				//set size
				m_CellToAdd.SetSize(cellWidth, cellHeight);

				//set pos

				float xPos = (col * cellWidth) + position.x;
				float yPos = (row * cellHeight) + position.y;

				m_CellToAdd.SetPos(xPos, yPos);


				//get input for col
				input >> value;


				//std::cout << value;

				switch (value)
				{
				case 0:
					m_CellToAdd.SetType(CellType::spawnable);
					break;
				case 1:
					m_CellToAdd.SetType(CellType::unspawnable);
					break;
				case 2:
					m_CellToAdd.SetType(CellType::teleport);
					break;
				}





				input >> value;
			



				switch (value)
				{
				case 5:
					//set to road
					m_CellToAdd.SetTexture("RoadTile.png");
					m_CellToAdd.SetCollision(false);
					if (m_CellToAdd.GetCellType() == CellType::spawnable)
					{
						m_SpawnMap.emplace_back(m_CellToAdd);
					}
					break;
				case 6:
					//set to wall
					m_CellToAdd.SetTexture("WallTile.png");
					m_CellToAdd.SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					m_CellToAdd.SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(m_CellToAdd);
					break;
				case 7:
					//set to tele[prt
					m_CellToAdd.SetTexture("Teleport.png");
					m_CellToAdd.SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					m_CellToAdd.SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(m_CellToAdd); //maybe change this?
					break;
				}



	
				m_Map.emplace_back(m_CellToAdd);





			}
		}

		input.close();

	}



	void TileMapComponent::Render()
	{

		for (size_t i = 0; i < m_Map.size(); ++i)
		{
			m_Map[i].Render();
		}

	}

	std::vector<Cell> TileMapComponent::GetMap()
	{
		return m_Map;

	}

	std::vector<Cell> TileMapComponent::GetCollisionMap()
	{
		return m_CollisionMap;
	}

	std::vector<Cell> TileMapComponent::GetSpawnMap()
	{
		return m_SpawnMap;
	}

}