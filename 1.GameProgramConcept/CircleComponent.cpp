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
    //����Բ�ľ��ƽ��
    Vector2 diff = a.GetCenter() - b.GetCenter();
    float distSq = diff.LengthSq();

    //������Բ�뾶֮�͵�ƽ��
    float radiisq = a.GetRadius() + b.GetRadius();
    radiisq *= radiisq;

    return distSq <= radiisq;
}
