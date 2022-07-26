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
		int mapSizeX;
		int mapSizeY;

		mapSizeX;
		mapSizeY;

		glm::vec2 position; //change to transform component later

		std::ifstream input(m_File);

		if (!input.is_open())
		{
			std::cout << "Opening file failed";
			return;
		}


		//create nested for loops to intialize each cell

	}

	void TileMapComponent::Render()
	{

		for (size_t i = 0; i < m_Map.size(); ++i)
		{
			m_Map[i].Render();
		}

	}

}