#include "MiniginPCH.h"
#include "TileMapComponent.h"
#include <fstream>

namespace dae
{
	TileMapComponent::TileMapComponent(GameObject* go, const char* filename): BaseComponent{go}, m_File{filename}
	{

	}

	TileMapComponent::~TileMapComponent()
	{



	}



	void TileMapComponent::ConvertFileToMap()
	{
		size_t mapSizeX;
		size_t mapSizeY;

		int value;

		//TODO: REMOVE = 1, temp for warining
		mapSizeX = 1;
		mapSizeY = 1;

		glm::vec2 position; //change to transform component later

		std::ifstream input(m_File);

		if (!input.is_open())
		{
			std::cout << "Opening file failed";
			return;
		}

		Cell cellToAdd;

		//create nested for loops to intialize each cell

		for (size_t row = 0; row < mapSizeY; ++row)
		{
			for (size_t col = 0; col < mapSizeX; ++col)
			{

				input >> value;

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

				input >> value;

				//if .. if.. -> set texture




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