#pragma once
#include "BaseComponent.h"
#include "Cell.h"

namespace dae
{

	class TileMapComponent final : public BaseComponent
	{

	public:

		TileMapComponent(GameObject* go, const char* filename);
		~TileMapComponent();



		void ConvertFileToMap();
		void Render();

		std::vector<Cell> GetMap();



	private:

		const char* m_File;

		std::vector<Cell> m_Map;


	};

}