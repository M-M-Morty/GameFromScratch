#pragma once

#include "component.h"
#include <unordered_map>
#include <string>

class AIComponent :public Component
{
public:
	AIComponent(class Actor* owner);

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);

	//往map中添加一个新的状态
	void RegisterState(class AIState* state);
private:
	//将状态的名字映射到一个状态实例上
	std::unordered_map<std::string, class AIState*> mStateMap;
	//当前状态
	class AIState* mCurrentState;
};


