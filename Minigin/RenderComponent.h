#pragma once
#include "BaseComponent.h"


namespace dae
{

	class Texture2D;

	class RenderComponent : public BaseComponent
	{

	public:
		RenderComponent(GameObject* go);
		~RenderComponent();
		void Update(float deltaTime) override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& texture);

		std::shared_ptr<Texture2D> GetTexture();

	private:



		std::shared_ptr<Texture2D> m_Texture{};

	};

}

