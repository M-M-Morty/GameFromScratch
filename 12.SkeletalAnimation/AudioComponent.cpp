#include "AudioComponent.h"
#include "Actor.h"
#include "AudioSystem.h"
#include "Game.h"

AudioComponent::AudioComponent(Actor* owner, int updateOrder)
    :Component(owner,updateOrder)
{
}

AudioComponent::~AudioComponent()
{
    StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
    Component::Update(deltaTime);

	//移除无效的2D/3D事件
	auto iter = mEvents2D.begin();
	while (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = mEvents3D.begin();
	while (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void AudioComponent::OnUpdateWorldTransform()
{
	Matrix4 world = mOwner->GetWorldTransform();
	for (auto& event : mEvents3D)
	{
		if (event.IsValid())
		{
			event.Set3DAttributes(world);
		}
	}
}

SoundEvent AudioComponent::PlayEvent(const std::string& name)
{
	SoundEvent e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	// Is this 2D or 3D?
	if (e.Is3D())
	{
		mEvents3D.emplace_back(e);
		// Set initial 3D attributes
		e.Set3DAttributes(mOwner->GetWorldTransform());
	}
	else
	{
		mEvents2D.emplace_back(e);
	}
	return e;
}

void AudioComponent::StopAllEvents()
{
	//停止所有的声音
	for (auto& e : mEvents2D)
	{
		e.Stop();
	}
	for (auto& e : mEvents3D)
	{
		e.Stop();
	}
	//清除事件数组
	mEvents2D.clear();
	mEvents3D.clear();
}
