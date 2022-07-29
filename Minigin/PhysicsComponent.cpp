#include "MiniginPCH.h"
#include "PhysicsComponent.h"

namespace dae
{

	PhysicsComponent::PhysicsComponent(GameObject* go, TransformComponent* transformComp, RectColliderComponent* colliderComp) : BaseComponent{ go }, m_pTransformComp{ transformComp }, m_pColliderComp{ colliderComp }, m_Velocity{ 0,0 }
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{
		delete m_pColliderComp;
		m_pColliderComp = nullptr;
	}

	void PhysicsComponent::Update(float deltaTime)
	{
		//move transform(go with visual) and collider(collision) depending on the velocity
		
		
		m_pTransformComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);
		m_pColliderComp->Move(m_Velocity.x * deltaTime, m_Velocity.y * deltaTime);

	}



	RectColliderComponent* PhysicsComponent::GetColliderComponent()
	{
		return m_pColliderComp;
	}

	void PhysicsComponent::SetVelocity(Velocity velocity)
	{
		m_Velocity = velocity;
	}

	void PhysicsComponent::SetXVelocity(float xVelocity)
	{
		m_Velocity.x = xVelocity;
	}

	void PhysicsComponent::SetYVelocity(float yVelocity)
	{
		m_Velocity.y = yVelocity;
	}

	Velocity PhysicsComponent::GetVelocity()
	{
		return m_Velocity;
	}

	void PhysicsComponent::HandleCollision(RectColliderComponent* collision)
	{

		collision;
	}

}