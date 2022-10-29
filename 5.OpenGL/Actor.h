#pragma once
#include "Game.h"
#include "Math.h"
#include "Component.h"


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

	
	void Update(float deltaTime);//由Game实例调用的更新每一个actor的函数
	void UpdateComponts(float deltaTime);//更新所有附加到actor上的组件
	virtual void UpdateActor(float deltaTime);//任何具体的actor的更新代码（派生类去实现）

	//由游戏实例调用的处理actor输入的函数
	void ProcessInput(const uint8_t* keyState);
	//由actor子类重写的处理输入的函数
	virtual void ActorInput(const uint8_t* keyState);
	//getter和setter函数
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale()const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation()const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation),-Math::Sin(mRotation)); }

	State GetState()const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	//添加或删除组件
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State mState;//actor的状态

	Matrix4 mWorldTransform;
	Vector2 mPosition;//actor的位置
	float mScale;//actor的缩放
	float mRotation;//actor的旋转角度（弧度制）
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;//管理附属在actor上的components
	class Game* mGame;//通过依赖注入的方式（拥有Game类对象的指针），从而访问Game类对象
};
