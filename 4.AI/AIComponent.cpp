#include "AIComponent.h"
#include "AIState.h"
#include <SDL/SDL_log.h>

AIComponent::AIComponent(Actor* owner)
	:Component(owner)
{
}

void AIComponent::Update(float deltaTime)
{
	mCurrentState->Update(deltaTime);
}

void AIComponent::ChangeState(const std::string& name)
{
	//�����뿪��ǰ״̬
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		//��ʼ�����µ�״̬
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		mCurrentState = nullptr;
	}


}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}


