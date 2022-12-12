#include "FollowCamera.h"

#include "Actor.h"

Vector3 FollowCamera::ComputeCameraPos() const
{
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}

FollowCamera::FollowCamera(Actor* owner)
	:CameraComponent(owner)
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	// Compute dampening from spring constant
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	// Compute ideal position
	Vector3 idealPos = ComputeCameraPos();
	// Compute difference between actual and ideal
	Vector3 diff = mActualPos - idealPos;
	// Compute acceleration of spring
	Vector3 acel = -mSpringConstant * diff -
		dampening * mVelocity;
	// Update velocity
	mVelocity += acel * deltaTime;
	// Update actual camera position
	mActualPos += mVelocity * deltaTime;
	// Target is target dist in front of owning actor
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	// Use actual position here, not ideal
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	mActualPos = ComputeCameraPos();
	mVelocity = Vector3::Zero;
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}
