#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
    :Component(owner)
    ,mRadius(0.f)
{
    
}

const Vector2& CircleComponent::GetCenter() const
{
    return mOwner->GetPosition();
}

float CircleComponent::GetRadius() const
{
    return mOwner->GetScale() * mRadius;
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
    //计算圆心距的平方
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    //计算两圆半径之和的平方
    float radiisq = a.GetRadius() + b.GetRadius();
    radiisq *= radiisq;

    return distSq <= radiisq;
}
