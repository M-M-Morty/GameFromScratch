#pragma once
#include <cstdint>

class Component
{
public:
	//updateOrder��ֵԽС�������Խ�����
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	
	//����deltaTime�������
	virtual void Update(float deltaTime);
	//Ϊ��ǰ�����������
	virtual void ProcessInput(const uint8_t* keyState){}

	virtual void OnUpdateWorldTransform(){}

	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//ӵ�и������actor
	class Actor* mOwner;//ӵ�и������actor
	
	//����ĸ���˳��
	int mUpdateOrder;
private:
};