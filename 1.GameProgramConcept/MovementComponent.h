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
	//������ת�ٶ�
	float mAngularSpeed;
	//�����ƶ��ٶ�
	float mForwardSpeed;
};

