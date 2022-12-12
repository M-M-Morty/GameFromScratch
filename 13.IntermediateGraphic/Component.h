#pragma once
#include <cstdint>

class Component
{
public:
	//updateOrder数值越小，组件就越早更新
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	
	//根据deltaTime更新组件
	virtual void Update(float deltaTime);
	//为当前组件处理输入
	virtual void ProcessInput(const uint8_t* keyState){}

	virtual void OnUpdateWorldTransform(){}

	class Actor* GetOwner() { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//拥有该组件的actor
	class Actor* mOwner;
	
	//组件的更新顺序
	int mUpdateOrder;
private:
};