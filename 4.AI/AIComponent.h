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

	//��map�����һ���µ�״̬
	void RegisterState(class AIState* state);
private:
	//��״̬������ӳ�䵽һ��״̬ʵ����
	std::unordered_map<std::string, class AIState*> mStateMap;
	//��ǰ״̬
	class AIState* mCurrentState;
};


