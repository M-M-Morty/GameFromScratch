#pragma once
#include "Actor.h"
class Component
{
public:
	
	Component(class Actor* owner, int updateOrder = 100);//updateOrder��ֵԽС�������Խ�����
	virtual ~Component();
	
	virtual void Update(float deltaTime);//����deltaTime�������
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;//ӵ�и�����Ķ���
	
	int mUpdateOrder;//����ĸ���˳��
private:
};