#pragma once

#include "MovementComponent.h"

class InputComponent :public MoveComponent
{
public:
	InputComponent(class Actor* owner);

	virtual void ProcessInput(const struct InputState& state) override;

	//为私有成员变量设置的getter/setter函数
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
	//最大前进速度和旋转速度
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	//为前进/后退运动设置的key值
	int mForwardKey;
	int mBackKey;

	//为旋转运动设置的key值
	int mClockwiseKey;
	int mCounterClockwiseKey;
};