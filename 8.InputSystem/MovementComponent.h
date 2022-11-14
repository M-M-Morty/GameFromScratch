#pragma once
#include "Component.h"

class MoveComponent :public Component 
{
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	
	virtual void Update(float deltaTime)override;

	float GetAngularSpeed()const { return mAngularSpeed; }
	float GetForwardSpeed()const { return mForwardSpeed; }
	void  SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void  SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	//控制旋转速度
	float mAngularSpeed;
	//控制移动速度
	float mForwardSpeed;
};

