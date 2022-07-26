#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "BaseColliderComponent.h"
namespace dae
{
    struct Velocity
    {
        float x;
        float y;
        
    };

    class PhysicsComponent final: public BaseComponent
    {

    public:

        PhysicsComponent(GameObject* go, TransformComponent* transformComp, BaseColliderComponent* colliderComp);
        ~PhysicsComponent();

        virtual void Update(float deltaTime) override;

        void SetVelocity(Velocity velocity);

        void SetXVelocity(float xVelocity);

        void SetYVelocity(float yVelocity);

       BaseColliderComponent* GetColliderComponent();
       
       Velocity GetVelocity();

    private:


        Velocity m_Velocity;
        TransformComponent* m_pTransformComp;
        BaseColliderComponent* m_pColliderComp;
      


    };

}

