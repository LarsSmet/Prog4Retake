#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "RectColliderComponent.h"

namespace dae
{
    struct Velocity
    {
        float x;
        float y;

    };


    class PhysicsComponent : public BaseComponent
    {

    public:

        PhysicsComponent(GameObject* go, TransformComponent* transformComp, RectColliderComponent* colliderComp);
        ~PhysicsComponent();

        virtual void Update(float deltaTime) override;

        void SetVelocity(Velocity velocity);

        void SetXVelocity(float xVelocity);

        void SetYVelocity(float yVelocity);

        RectColliderComponent* GetColliderComponent();

        Velocity GetVelocity();

        void HandleCollision(RectColliderComponent* collision);
        TransformComponent* GetTransformComp();


    private:


        Velocity m_Velocity;
        TransformComponent* m_pTransformComp;
        RectColliderComponent* m_pColliderComp;



    };

}