#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "RectColliderComponent.h"
#include "Cell.h"

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

        std::shared_ptr<RectColliderComponent> GetColliderComponent();

        Velocity GetVelocity();

        bool HandleCollision(RectColliderComponent* collision);
        TransformComponent* GetTransformComp();

        void HandleLevelCollision();

        bool HandleCollision(Rectf collision);


    private:


        Velocity m_Velocity;
        TransformComponent* m_pTransformComp;
        std::shared_ptr <RectColliderComponent> m_pColliderComp;

        std::vector<std::shared_ptr<Cell>> m_CellsToCheck;

    };

}