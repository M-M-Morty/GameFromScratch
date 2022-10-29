#pragma once
#include<vector>
#include "Math.h"

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	//由Game实例调用的更新每一个actor的函数
	void Update(float deltaTime);
	//更新所有附加到actor上的组件
	void UpdateComponts(float deltaTime);
	//任何具体的actor的更新代码（派生类去实现）
	virtual void UpdateActor(float deltaTime);

	//getter和setter函数
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale()const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation()const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation),-Math::Sin(mRotation)); }
	State GetState()const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	//添加或删除组件
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;//actor的状态

	Vector2 mPosition;//actor的位置
	float mScale;//actor的缩放
	float mRotation;//actor的旋转角度（弧度制）

	std::vector<class Component*> mComponents;//管理附属在actor上的components
	class Game* mGame;//通过依赖注入的方式（拥有Game类对象的指针），从而访问Game类对象
};
