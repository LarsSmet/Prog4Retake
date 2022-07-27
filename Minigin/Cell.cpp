#include "MiniginPCH.h"
#include "Cell.h"

namespace dae
{

	Cell::Cell()
	{
	}

	Cell::~Cell()
	{
	}

	void Cell::Render()
	{
		//Renderer::GetInstance().RenderTexture(*texture, pos.x, pos.y);
	}

	void Cell::SetTexture(const std::string& filename)
	{
		//m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		filename;
	}

	void Cell::SetCollision(bool hasCol)
	{
		//m_HasCollision = isCol;
		hasCol;
	}

}
