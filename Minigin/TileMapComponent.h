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
		std::vector<Cell> GetCollisionMap();
		std::vector<Cell> GetSpawnMap();


	private:

		const char* m_File;

		std::vector<Cell> m_Map;
		std::vector<Cell> m_CollisionMap;
		std::vector<Cell> m_SpawnMap;
		

		GameObject* m_Go;


		Cell m_CellToAdd;

	};

}