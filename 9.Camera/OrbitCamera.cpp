#include "OrbitCamera.h"
#include "Actor.h"


OrbitCamera::OrbitCamera(Actor* owner)
	:CameraComponent(owner)
	,mPitchSpeed(0.f)
	,mYawSpeed(0.f)
	,mOffset(-400.f,0.f,0.f)
	,mUp(Vector3::UnitZ)
{
}

void OrbitCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);

	Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
	// Transform offset and up by yaw
	mOffset = Vector3::Transform(mOffset, yaw);
	mUp = Vector3::Transform(mUp, yaw);

	Vector3 forward = -1.0f * mOffset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(mUp, forward);
	right.Normalize();

	// Create quaternion for pitch about camera right
	Quaternion pitch(right, mPitchSpeed * deltaTime);
	// Transform camera offset and up by pitch
	mOffset = Vector3::Transform(mOffset, pitch);
	mUp = Vector3::Transform(mUp, pitch);

	Vector3 target = mOwner->GetPosition();
	Vector3 cameraPos = target + mOffset;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
	SetViewMatrix(view);
}
