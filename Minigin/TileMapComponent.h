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

		std::vector<std::shared_ptr<Cell>> GetMap();
		std::vector<std::shared_ptr<Cell>> GetCollisionMap();
		std::vector<std::shared_ptr<Cell>> GetSpawnMap();


	private:

		const char* m_File;

		std::vector<std::shared_ptr<Cell>> m_Map;
		std::vector<std::shared_ptr<Cell>> m_CollisionMap;
		std::vector<std::shared_ptr<Cell>> m_SpawnMap;
		

		GameObject* m_Go;


		

	};

}