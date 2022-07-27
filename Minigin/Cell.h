#pragma once
#include "Texture2D.h"

namespace dae
{

	class Cell
	{


	public:

		Cell();
		~Cell();


		void Render();
		void SetTexture(const std::string& filename);
		void SetCollision(bool hasCol);

	private:

		int m_Id;
		bool m_HasCollision;

		float m_xPos;
		float m_yPos;

		float m_Width;
		float m_Height;

		std::shared_ptr<dae::Texture2D> m_Texture;

		//render


	};

}