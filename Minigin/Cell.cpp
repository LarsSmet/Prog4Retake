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
	/*	if (m_pColliderComp != nullptr)
		{
			delete m_pColliderComp;
			m_pColliderComp = nullptr;
		}*/

		//if (m_HasCollision)
		//{
		//	delete m_pColliderComp;
		//	m_pColliderComp = nullptr;
		//}

		//delete m_pColliderComp;
			//m_pColliderComp = nullptr;

	}

	void Cell::Render()
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_xPos, m_yPos);
	}

	void Cell::SetTexture(const std::string& filename)
	{
		m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		
	}

	void Cell::SetCollision(bool hasCol, RectColliderComponent colliderComp)
	{
		m_HasCollision = hasCol;

		if (hasCol)
		{
			m_pColliderComp = std::make_shared<RectColliderComponent>(colliderComp);
		}
		
	}

	void Cell::SetCollision(bool hasCol, Rectf collider)
	{
		m_HasCollision = hasCol;

		if (hasCol)
		{
			m_RectCollider = collider;
		}

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

	bool Cell::HasCollision()
	{
		return true;
	}

	void Cell::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}

	void Cell::SetType(CellType type)
	{
		m_CellType = type;
	}

	std::shared_ptr<RectColliderComponent> Cell::GetCollider()
	{
		return m_pColliderComp;
	}

	Rectf Cell::GetRectCollider()
	{
		return m_RectCollider;
	}

	CellType Cell::GetCellType()
	{
		return m_CellType;
	}


}
