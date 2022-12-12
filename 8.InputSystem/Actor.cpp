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
	mGame->RemoveActor(this);//����Ϸʵ�����Ƴ��ö���

	while (!mComponents.empty())
	{
		delete mComponents.back();//���ȵ���mComponent������������ͨ��mOwerָ���Actor��
								 //�������ҵ�componentָ���vector�������Ƴ�ָ�������ָ��
	}


}

void Actor::Update(float deltaTime)//���¾���actor�������Ϊ������������componts����Ϊ
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

void Actor::ProcessInput(const struct InputState& state)
{
	if (mState == EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput(state);
		}
		ActorInput(state);
	}
}

void Actor::ActorInput(const struct InputState& state)
{
}


void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// Scale, then rotate, then translate
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateRotationZ(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(Vector3(mPosition.x, mPosition.y, 0.0f));

		// Inform components world transform updated
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	//ͨ��component��updateOrderֵ���ҵ���Ӧ���ڵ�λ�ò�����
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
