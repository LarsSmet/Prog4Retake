#include "MiniginPCH.h"
#include "RectColliderComponent.h"
#include "GameObject.h"

namespace dae
{
	RectColliderComponent::RectColliderComponent(GameObject* go, Rectf rectCollider) : BaseComponent(go), m_RectCollider{rectCollider}
	{

	}

	RectColliderComponent::~RectColliderComponent()
	{
		/*delete m_RectCollider;
		m_RectCollider = nullptr;*/

	}
	CollisionHitInfo RectColliderComponent::OnCollision(RectColliderComponent* collision)
	{
		CollisionHitInfo collisionInfo;

		
		auto rectCol = collision->GetRectCollider();

		




		/*if (rectCol != nullptr)
		{*/


			//create vertices
			Point2f colLeftBot{ rectCol.left, rectCol.bottom };
			Point2f colRightBot{ rectCol.left + rectCol.width, rectCol.bottom };
			Point2f colRightTop{ rectCol.left + rectCol.width, rectCol.bottom + rectCol.height };
			Point2f colLeftTop{ rectCol.left, rectCol.bottom + rectCol.height };

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

			//Point2f midTop{ m_RectCollider.left + m_RectCollider.width / 2, m_RectCollider.bottom - m_RectCollider.height };
			//Point2f midBot{ m_RectCollider.left + m_RectCollider.width / 2, m_RectCollider.bottom };
			//Point2f midLeft{ m_RectCollider.left, m_RectCollider.bottom + m_RectCollider.height / 2 };
			//Point2f midRight{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom + m_RectCollider.height / 2 };
			//Point2f leftBot{ m_RectCollider.left, m_RectCollider.bottom };
			//Point2f leftTop{ m_RectCollider.left, m_RectCollider.bottom - m_RectCollider.height };
			//Point2f rightTop{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom - m_RectCollider.height };
			//Point2f rightBot{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom };





			Point2f midTop{ m_RectCollider.left + m_RectCollider.width / 2, m_RectCollider.bottom - m_RectCollider.height };
			Point2f midBot{ m_RectCollider.left + (m_RectCollider.width / 2), m_RectCollider.bottom };
			Point2f midLeft{ m_RectCollider.left, m_RectCollider.bottom - (m_RectCollider.height / 2) };
			Point2f midRight{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom - ( m_RectCollider.height / 2) };
			Point2f leftBot{ m_RectCollider.left, m_RectCollider.bottom };
			Point2f leftTop{ m_RectCollider.left, m_RectCollider.bottom - m_RectCollider.height };
			Point2f rightTop{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom - m_RectCollider.height };
			Point2f rightBot{ m_RectCollider.left + m_RectCollider.width, m_RectCollider.bottom };


			//left col
			if (utils::Raycast(vertices, Point2f{ leftBot.x, leftBot.y - 3 }, Point2f{ midBot.x, midBot.y - 3 }, collisionInfo.leftColBot))
			{
				//std::cout << "raycast correct";
				collisionInfo.leftColBotIsHit = true;
			}
			if (utils::Raycast(vertices, Point2f{ leftTop.x, leftTop.y + 3 }, Point2f{ midTop.x, midTop.y + 3}, collisionInfo.leftColTop))
			{
				collisionInfo.leftColTopIsHit = true;
			}

			//right col

			if (utils::Raycast(vertices, Point2f{ rightBot.x, rightBot.y - 3 }, Point2f{ midBot.x, midBot.y - 3 }, collisionInfo.rightColBot))
			{
				collisionInfo.rightColBotIsHit = true;
			}
			if (utils::Raycast(vertices, Point2f{ rightTop.x, rightTop.y + 3 }, Point2f{ midTop.x, midTop.y + 3 }, collisionInfo.rightColTop))
			{
				collisionInfo.rightColTopIsHit = true;
			}
			//bot col
			if (utils::Raycast(vertices, Point2f{ leftBot.x + 3, leftBot.y }, Point2f{ midLeft.x + 3, midLeft.y }, collisionInfo.botColLeft))
			{
				collisionInfo.botColLeftIsHit = true;
			}
			if (utils::Raycast(vertices, Point2f{ rightBot.x - 3, rightBot.y }, Point2f{ midRight.x - 3,midRight.y }, collisionInfo.botColRight))
			{
				collisionInfo.botColRightIsHit = true;
			}
			//top col
			if (utils::Raycast(vertices, Point2f{ leftTop.x + 3, leftTop.y }, Point2f{ midLeft.x + 3, midLeft.y }, collisionInfo.topColLeft))
			{
				collisionInfo.topColLeftIsHit = true;
			}
			if (utils::Raycast(vertices, Point2f{ rightTop.x - 3, rightTop.y }, Point2f{ midRight.x - 3, midRight.y }, collisionInfo.topColRight))
			{
				collisionInfo.topColRightIsHit = true;
			}



			return collisionInfo;




		//}



		//return CollisionHitInfo();



	}
	void RectColliderComponent::SetXPosition(float x)
	{
		m_RectCollider.left = x;
		
	}

	void RectColliderComponent::SetYPosition(float y)
	{

		m_RectCollider.bottom = y;
	}

	void RectColliderComponent::SetPosition(float x, float y)
	{
		m_RectCollider.left = x;
		m_RectCollider.bottom = y;
	}





	Point2f RectColliderComponent::GetPosition() const
	{
		return Point2f{ m_RectCollider.left, m_RectCollider.bottom};
	}
	void RectColliderComponent::Move(float xOffSet, float yOffSet)
	{
		SetPosition(m_RectCollider.left + xOffSet, m_RectCollider.bottom + yOffSet);
	}
	Rectf RectColliderComponent::GetRectCollider()
	{
		return m_RectCollider;
	}
}