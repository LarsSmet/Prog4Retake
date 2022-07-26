#include "MiniginPCH.h"
#include "VerticesCollider.h"
#include "SVGParser.h"

namespace dae
{



	VerticesCollider::VerticesCollider(GameObject* go, bool isTrigger, std::vector<std::vector<Point2f>>* pVertices) : BaseColliderComponent(go, isTrigger), m_pVertices{ pVertices }
	{

	}

	VerticesCollider::~VerticesCollider()
	{
		delete m_pVertices;
		m_pVertices = nullptr;
	}

	CollisionHitInfo VerticesCollider::OnCollision(BaseColliderComponent* collision)
	{
		collision;
		return CollisionHitInfo();
	}

	bool VerticesCollider::OnTrigger(BaseColliderComponent* collision)
	{
		collision;
		return true;
	}

	void VerticesCollider::SetPosition(const float x, const float y)
	{
		x;
		y;
	}

	void VerticesCollider::Move(float xOffSet, float yOffSet)
	{
		xOffSet;
		yOffSet;
	}

	Rectf* VerticesCollider::GetRectCollider() const
	{
		return nullptr;
	}


	Point2f VerticesCollider::GetPosition() const
	{
		return Point2f();
	}

	std::vector<std::vector<Point2f>>* VerticesCollider::GetVerticesCollider() const
	{
		
		return m_pVertices;
		
	}




}