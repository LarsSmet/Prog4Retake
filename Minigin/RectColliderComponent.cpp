#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

namespace dae
{
	RectColliderComponent::RectColliderComponent(GameObject* go) : BaseComponent(go)
	{

	}

	RectColliderComponent::~RectColliderComponent()
	{
		delete m_RectCollider;
		m_RectCollider = nullptr;

	}
	CollisionHitInfo RectColliderComponent::OnCollision(RectColliderComponent* collision)
	{
		CollisionHitInfo collisionInfo;

		
		auto rectCol = collision->GetRectCollider();

		




		if (rectCol != nullptr)
		{


			//create vertices
			Point2f colLeftBot{ rectCol->left, rectCol->bottom };
			Point2f colRightBot{ rectCol->left + rectCol->width, rectCol->bottom };
			Point2f colRightTop{ rectCol->left + rectCol->width, rectCol->bottom + rectCol->height };
			Point2f colLeftTop{ rectCol->left, rectCol->bottom + rectCol->height };

			std::vector<Point2f> vertices{ colLeftBot,colRightBot,colRightTop, colLeftTop };

			//utils::HitInfo colLeftBotInfo;
			//utils::HitInfo colLeftTopInfo;
			//utils::HitInfo colTopLeftInfo;
			//utils::HitInfo colTopRightInfo;
			//utils::HitInfo colRightTopInfo;
			//utils::HitInfo colRightBotInfo;
			//utils::HitInfo colBotRightInfo;
			//utils::HitInfo colBotLeftInfo;


			//create raycast points

			Point2f midTop{ m_RectCollider->left + m_RectCollider->width / 2, m_RectCollider->bottom + m_RectCollider->height };
			Point2f midBot{ m_RectCollider->left + m_RectCollider->width / 2, m_RectCollider->bottom };
			Point2f midLeft{ m_RectCollider->left, m_RectCollider->bottom + m_RectCollider->height / 2 };
			Point2f midRight{ m_RectCollider->left + m_RectCollider->width, m_RectCollider->bottom + m_RectCollider->height / 2 };
			Point2f leftBot{ m_RectCollider->left, m_RectCollider->bottom };
			Point2f leftTop{ m_RectCollider->left, m_RectCollider->bottom + m_RectCollider->height };
			Point2f rightTop{ m_RectCollider->left + m_RectCollider->width, m_RectCollider->bottom + m_RectCollider->height };
			Point2f rightBot{ m_RectCollider->left + m_RectCollider->width, m_RectCollider->bottom };



			//left col
			utils::Raycast(vertices, leftBot, midBot, collisionInfo.leftColBot);
			utils::Raycast(vertices, leftTop, midTop, collisionInfo.leftColTop);
			

			//right col
			utils::Raycast(vertices, rightBot, midBot, collisionInfo.rightColBot);
			utils::Raycast(vertices, rightTop, midTop, collisionInfo.rightColTop);

			//bot col
			utils::Raycast(vertices, leftBot, midLeft, collisionInfo.botColLeft);
			utils::Raycast(vertices, rightBot, midRight, collisionInfo.botColRight);

			//top col
			utils::Raycast(vertices, leftTop, midLeft, collisionInfo.topColLeft);
			utils::Raycast(vertices, rightTop, midRight, collisionInfo.topColRight);



			return collisionInfo;




		}



		return CollisionHitInfo();



	}


	void RectColliderComponent::SetPosition()
	{

	}

	Point2f RectColliderComponent::GetPosition() const
	{
		return Point2f();
	}
	void RectColliderComponent::Move(float xOffSet, float yOffSet)
	{
		xOffSet;
		yOffSet;
	}
	Rectf* RectColliderComponent::GetRectCollider()
	{
		return m_RectCollider;
	}
}