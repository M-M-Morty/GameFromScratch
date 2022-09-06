#pragma once
#include "Actor.h"
class Component
{
public:
	
	Component(class Actor* owner, int updateOrder = 100);//updateOrder数值越小，组件就越早更新
	virtual ~Component();
	
	virtual void Update(float deltaTime);//根据deltaTime更新组件
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	class Actor* mOwner;//拥有该组件的对象
	
	int mUpdateOrder;//组件的更新顺序
private:
};