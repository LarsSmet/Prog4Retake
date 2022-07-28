#include "MiniginPCH.h"
#include "TileMapComponent.h"
#include <fstream>
#include"ResourceManager.h"

namespace dae
{
	TileMapComponent::TileMapComponent(GameObject* go, const char* filename): BaseComponent{go}, m_File{filename}
	{
		//ConvertFileToMap();
	}

	TileMapComponent::~TileMapComponent()
	{

	

	}



	void TileMapComponent::ConvertFileToMap()
	{
		ResourceManager::GetInstance().Init("../Data/");

		size_t amountOfCol;
		size_t amountOfRows;

		float cellWidth;
		float cellHeight;

		int value;


		glm::vec2 position{0,0}; //change to transform component later

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

		Cell cellToAdd;



		//create nested for loops to intialize each cell

		for (size_t row = 0; row < amountOfRows; ++row)
		{
			for (size_t col = 0; col < amountOfCol; ++col)
			{
				//get input for col
				input >> value;


				//std::cout << value;

				if (value == 0)
				{
					//set col is false
					cellToAdd.SetCollision(false);
				}
				else if (value == 1)
				{
					//set col to true
					cellToAdd.SetCollision(true);
				}

				//get input for texture
				input >> value;
				//std::cout << value;

				switch (value)
				{
				case 2:
					//set to road
					cellToAdd.SetTexture("RoadTile.png");
					break;
				case 3:
					//set to wall
					cellToAdd.SetTexture("WallTile.png");
					break;
				}

				
				cellToAdd.SetPos((col * cellWidth) + position.x, (row * cellHeight) + position.y);

				m_Map.emplace_back(cellToAdd);


			


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

}