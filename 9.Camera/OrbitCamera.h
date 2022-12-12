#pragma once
#include "CameraComponent.h"
#include "Math.h"

class OrbitCamera :public CameraComponent
{
public:
	OrbitCamera(class Actor* owner);

	void Update(float deltaTime) override;

	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	//与目标物体位置的偏移
	Vector3 mOffset;
	Vector3 mUp;
	float mPitchSpeed;
	float mYawSpeed;
};