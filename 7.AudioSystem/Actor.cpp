#include "Actor.h"
#include "Math.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive)
	,mPosition(Vector3::Zero)
	,mRotation(Quaternion::Identity)
	,mScale(1.0f)
	,mGame(game)	
	,mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);//����Ϸʵ�����Ƴ��ö���

	while (!mComponents.empty())
	{
		delete mComponents.back();//���ȵ���mComponent������������ͨ��mOwerָ���Actor��
								 //�������ҵ�componentָ���vector�������Ƴ�ָ��������ָ��
	}


}

void Actor::Update(float deltaTime)//���¾���actor��������Ϊ������������componts����Ϊ
{
	if (mState == EActive)
	{
		ComputeWorldTransform();

		UpdateActor(deltaTime);
		UpdateComponts(deltaTime);

		ComputeWorldTransform();
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

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

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