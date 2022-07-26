#pragma once
#include "BaseColliderComponent.h"

namespace dae
{

    class VerticesCollider : public BaseColliderComponent
    {
    
    
    public:
        VerticesCollider(GameObject* go, bool isTrigger, std::vector<std::vector<Point2f>>* pVertices);
        ~VerticesCollider();



    private:


        virtual CollisionHitInfo OnCollision(BaseColliderComponent* collision);
        virtual bool OnTrigger(BaseColliderComponent* collision);

        virtual void SetPosition(const float x, const float y);
        virtual void Move(float xOffSet, float yOffSet);

        virtual Rectf* GetRectCollider() const;
      

        virtual Point2f GetPosition() const;

        virtual std::vector<std::vector<Point2f>>* GetVerticesCollider() const override;
    

        std::vector<std::vector<Point2f>>* m_pVertices;

    };

}

