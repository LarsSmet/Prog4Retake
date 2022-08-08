#include "MiniginPCH.h"
#include "TileMapComponent.h"
#include <fstream>
#include"ResourceManager.h"
#include "GameObject.h"

namespace dae
{
	TileMapComponent::TileMapComponent(GameObject* go, const char* filename): BaseComponent{go}, m_File{filename}, m_Go{go}
	{

	
	}

	TileMapComponent::~TileMapComponent()
	{

		//delete m_File;
		//m_File = nullptr;

	}





	void TileMapComponent::ConvertFileToMap()
	{


		ResourceManager::GetInstance().Init("../Data/");

	

		float cellWidth;
		float cellHeight;

		int value;

		auto transformCompPos = m_Go->GetTransformComp()->GetPosition();

		m_Pos.x = transformCompPos.x;
		m_Pos.y = transformCompPos.y;
		glm::vec2 position{ transformCompPos.x, transformCompPos.y }; //change to transform component later

		

		std::ifstream input(m_File);

		if (!input.is_open())
		{
			std::cout << "Opening file failed";
			return;
		}

		//first value read is the amount of col, second value is the amount of rows
		//third value is the cell width, fourth value is the cell height
		input >> m_AmountOfCol;
		input >> m_AmountOfRows;
		input >> cellWidth;
		input >> cellHeight;
		m_CellWidth = cellWidth;
		m_CellHeight = cellHeight;

		//create nested for loops to intialize each cell

		for (size_t row = 0; row < m_AmountOfRows; ++row)
		{
			for (size_t col = 0; col < m_AmountOfCol; ++col)
			{
				std::shared_ptr<Cell> cellToAdd = std::make_shared<Cell>();

				//set size
				cellToAdd->SetSize(cellWidth, cellHeight);
			

				//set pos

				float xPos = (col * cellWidth) + position.x;
				float yPos = (row * cellHeight) + position.y;

				cellToAdd->SetPos(xPos, yPos);


				//get input for col
				input >> value;


				//std::cout << value;

				switch (value)
				{
				case 0:
					cellToAdd->SetType(CellType::spawnable);
					break;
				case 1:
					cellToAdd->SetType(CellType::unspawnable);
					break;
				case 2:
					cellToAdd->SetType(CellType::teleport);
					break;
				}





				input >> value;
			



				switch (value)
				{
				case 5:
					//set to road
					cellToAdd->SetTexture("RoadTile.png");
					cellToAdd->SetCollision(false);
					if (cellToAdd->GetCellType() == CellType::spawnable)
					{
						m_SpawnMap.emplace_back(cellToAdd);
					}
					break;
				case 6:
					//set to wall
					cellToAdd->SetTexture("WallTile.png");
				//	cellToAdd->SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					cellToAdd->SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(cellToAdd);
					break;
				case 7:
					//set to tele[prt
					cellToAdd->SetTexture("Teleport.png");
					//cellToAdd->SetCollision(true, RectColliderComponent{ m_Go,  Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight } });
					cellToAdd->SetCollision(true, Rectf{ xPos, yPos /*+ cellHeight*/, cellWidth, cellHeight });
					m_CollisionMap.emplace_back(cellToAdd); //maybe change this?
					break;
				}



	
				m_Map.emplace_back(cellToAdd);





			}
		}

		input.close();

	}



	void TileMapComponent::Render()
	{

		for (size_t i = 0; i < m_Map.size(); ++i)
		{
			m_Map[i]->Render();
		}

	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetMap() const
	{
		return m_Map;

	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetCollisionMap() const
	{
		return m_CollisionMap;
	}

	std::vector<std::shared_ptr<Cell>> TileMapComponent::GetSpawnMap() const
	{
		return m_SpawnMap;
	}

	std::shared_ptr<Cell> TileMapComponent::GetCell(Point2f pos)
	{
		//grid doesnt necessarily have to start at 0,0 in the console
		pos.x -= m_Pos.x;

		pos.y -= m_Pos.y;




		

		return GetCell(int(pos.x / m_CellWidth) , int(pos.y / m_CellHeight));
	}

	std::shared_ptr<Cell> TileMapComponent::GetCell(int col, int row)
	{
		if (col < 0)
		{
			col = 0;
		}

		if (col >= m_AmountOfCol)
		{
			col = m_AmountOfCol - 1;
		}

		if (row < 0)
		{
			row = 0;
		}

		if (row >= m_AmountOfRows)
		{
			row = m_AmountOfRows - 1;
		}


		int index = row * m_AmountOfCol + col;
		std::cout << " Index: " << index;

		return m_Map[index];


		 
	}

}