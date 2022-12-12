#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.f)
	,mForwardSpeed(0.f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetRotation();
		//创建旋转的四元数(绕z轴)
		float angle= mAngularSpeed * deltaTime;
		Quaternion inc(Vector3::UnitZ, angle);
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		Vector3 pos = mOwner->GetPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}
}
