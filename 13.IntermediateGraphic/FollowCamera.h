#pragma once
#include "CameraComponent.h"

class FollowCamera :public CameraComponent
{
private:
	Vector3 ComputeCameraPos() const;

	//实际相机的位置
	Vector3 mActualPos;
	//实际相机的速度
	Vector3 mVelocity;
	//弹性系数（值越高，弹簧刚度越大）
	float mSpringConstant;

	float mHorzDist;
	float mVertDist;
	float mTargetDist;

public:
	FollowCamera(class Actor* owner);

	void  Update(float deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
};