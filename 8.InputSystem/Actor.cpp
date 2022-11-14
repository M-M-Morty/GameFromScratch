#include "Actor.h"
#include "Math.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
	,mGame(game)	
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);//从游戏实例中移除该对象

	while (!mComponents.empty())
	{
		delete mComponents.back();//会先调用mComponent的析构函数，通过mOwer指针从Actor类
								 //对象中找到component指针的vector对象，再移除指向自身的指针
	}


}

void Actor::Update(float deltaTime)//更新具体actor自身的行为及附属的所有componts的行为
{
	if (mState == EActive)
	{
		UpdateActor(deltaTime);
		UpdateComponts(deltaTime);
	}
}

void Actor::UpdateComponts(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState)
{
}

void Actor::AddComponent(Component* component)
{
	//通过component的updateOrder值，找到其应该在的位置并插入
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
			break;
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
