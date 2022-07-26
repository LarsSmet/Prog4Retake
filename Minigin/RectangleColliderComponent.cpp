#include "MiniginPCH.h"
#include "RectangleColliderComponent.h"
#include "utils.h"


namespace dae
{



	RectangleColliderComponent::RectangleColliderComponent(GameObject* go, bool isTrigger, Rectf* colliderShape) : BaseColliderComponent{go, isTrigger}, m_pCollider{colliderShape}
	{

	}

	RectangleColliderComponent::~RectangleColliderComponent()
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}

	CollisionHitInfo RectangleColliderComponent::OnCollision(BaseColliderComponent* collision) //uses raycast
	{
		collision;

		CollisionHitInfo collisionInfo;


		auto rectCol = collision->GetRectCollider();
		auto circleCol = collision->GetCircleCollider();
		auto verticesCol = collision->GetVerticesCollider();

		Point2f mid{ m_pCollider->left + m_pCollider->width / 2,m_pCollider->bottom + m_pCollider->height / 2 };
		Point2f top{ m_pCollider->left + m_pCollider->width / 2, m_pCollider->bottom };
		Point2f bot{ m_pCollider->left + m_pCollider->width / 2, m_pCollider->bottom + m_pCollider->height };
		Point2f left{ m_pCollider->left, m_pCollider->bottom + m_pCollider->height / 2 };
		Point2f right{ m_pCollider->left + m_pCollider->width, m_pCollider->bottom + m_pCollider->height / 2 };

	
		//does raycast depending on what kind of collider
		if (circleCol != nullptr)
		{
			//potential to add a circle col func
		}

		if (rectCol != nullptr)
		{
			//create vertices
			Point2f leftBot{ rectCol->left, rectCol->bottom };
			Point2f rightBot{ rectCol->left + rectCol->width, rectCol->bottom };
			Point2f rightTop{ rectCol->left + rectCol->width, rectCol->bottom + rectCol->height};
			Point2f leftTop{ rectCol->left, rectCol->bottom + rectCol->height};

			std::vector<Point2f> vertices{ leftBot,rightBot,rightTop,leftTop };

			utils::HitInfo hitInfoHorizontal;
			utils::HitInfo hitInfoVertical;
			


			if (utils::Raycast(vertices, left, mid, collisionInfo.hitInfoHorizontal))
			{
				collisionInfo.horizontalHit = true;
				collisionInfo.leftHit = true;
			} 
			else if (utils::Raycast(vertices, right, mid, collisionInfo.hitInfoHorizontal))
			{
				collisionInfo.horizontalHit = true;
				collisionInfo.rightHit = true;
			}

			if (utils::Raycast(vertices, top, mid, collisionInfo.hitInfoVertical))
			{
				collisionInfo.verticalHit = true;
			}
			else if (utils::Raycast(vertices, bot, mid, collisionInfo.hitInfoVertical))
			{
				collisionInfo.verticalHit = true;
			}
			
			
			


			return collisionInfo;


			

		}


		if (verticesCol != nullptr)
		{


			auto &vertices = *verticesCol;
		
		

			for (size_t i{ 0 }; i < vertices.size(); i++)
			{
				

				if (utils::Raycast(verticesCol->at(i), left, mid, collisionInfo.hitInfoHorizontal))
				{
					collisionInfo.horizontalHit = true;
					collisionInfo.leftHit = true;
					//std::cout << "left hit true";
				}
				else if (utils::Raycast(verticesCol->at(i), right, mid, collisionInfo.hitInfoHorizontal))
				{
					collisionInfo.horizontalHit = true;
					collisionInfo.rightHit = true;

				}

				if (utils::Raycast(verticesCol->at(i), top, mid, collisionInfo.hitInfoVertical))
				{
					collisionInfo.verticalHit = true;
					

				}
				else if (utils::Raycast(verticesCol->at(i), bot, mid, collisionInfo.hitInfoVertical))
				{
					collisionInfo.verticalHit = true;
					collisionInfo.botHit = true;

				}

			}
			return collisionInfo;
		}


		return collisionInfo;
	}

	bool RectangleColliderComponent::OnTrigger(BaseColliderComponent* collision)  //uses onoverlap
	{
	
		
		auto otherRect = collision->GetRectCollider();
		auto otherCircle = collision->GetCircleCollider();
		
		//use overlap depending on if it overlaps a rect col or circle col
		if (otherRect != nullptr)
		{

			if (utils::IsOverlapping(*m_pCollider, *otherRect))
			{

				return true;
			}
		}
		
		if (otherCircle != nullptr)
		{
			utils::IsOverlapping(*m_pCollider, *otherCircle);
			return false;
		}

		return false;

	}
	void RectangleColliderComponent::SetPosition(const float x, const float y)
	{
		m_pCollider->left = x;
		m_pCollider->bottom = y;


	}
	void RectangleColliderComponent::Move(float xOffSet, float yOffSet)
	{
		SetPosition(m_pCollider->left + xOffSet, m_pCollider->bottom + yOffSet);
	}
	Rectf* RectangleColliderComponent::GetRectCollider() const
	{

		return m_pCollider;
	}

	Point2f RectangleColliderComponent::GetPosition() const
	{
		return Point2f{ m_pCollider->left, m_pCollider->bottom };
	}


}