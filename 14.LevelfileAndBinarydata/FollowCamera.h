#pragma once
#include "CameraComponent.h"

class FollowCamera :public CameraComponent
{
private:
	Vector3 ComputeCameraPos() const;

	//ʵ�������λ��
	Vector3 mActualPos;
	//ʵ��������ٶ�
	Vector3 mVelocity;
	//����ϵ����ֵԽ�ߣ����ɸն�Խ��
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