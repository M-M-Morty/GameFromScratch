#pragma once

#include "MovementComponent.h"

class InputComponent :public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	virtual void ProcessInput(const struct InputState& state) override;

	//Ϊ˽�г�Ա�������õ�getter/setter����
	float GetMaxForward() const { return mMaxForwardSpeed; }
	float GetMaxAngular() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackKey() const { return mBackKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetCounterClockwiseKey() const { return mCounterClockwiseKey; }

	void SetMaxForwardSpeed(float speed) { mMaxForwardSpeed = speed; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackKey(int key) { mBackKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }

private:
	//���ǰ���ٶȺ���ת�ٶ�
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	//Ϊǰ��/�����˶����õ�keyֵ
	int mForwardKey;
	int mBackKey;

	//Ϊ��ת�˶����õ�keyֵ
	int mClockwiseKey;
	int mCounterClockwiseKey;
};