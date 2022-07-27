#include "MiniginPCH.h"
#include "Cell.h"
#include "Renderer.h"
#include "ResourceManager.h"

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
		Renderer::GetInstance().RenderTexture(*m_Texture, m_xPos, m_yPos);
	}

	void Cell::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		
	}

	void Cell::SetCollision(bool hasCol)
	{
		m_HasCollision = hasCol;
		
	}

	void Cell::SetPos(float x, float y)
	{

		m_xPos = x;
		m_yPos = y;

	}

	

}
