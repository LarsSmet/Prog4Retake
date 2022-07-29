#pragma once
#include "Texture2D.h"
#include "RectColliderComponent.h"

namespace dae
{

	class Cell
	{


	public:

		Cell();
		~Cell();


		void Render();
		void SetTexture(const std::string& filename);
		void SetCollision(bool hasCol, RectColliderComponent colliderComp);
		void SetCollision(bool hasCol);
		void SetPos(float x, float y);
		bool HasCollision();
		void SetSize(float width, float height);


		std::shared_ptr<RectColliderComponent> GetCollider();



	private:

		int m_Id;
		bool m_HasCollision;

		float m_xPos;
		float m_yPos;

		float m_Width;
		float m_Height;

		std::shared_ptr<dae::Texture2D> m_Texture;

		std::shared_ptr < RectColliderComponent> m_pColliderComp;


		//render


	};

}