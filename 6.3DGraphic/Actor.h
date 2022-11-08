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

	void ComputeWorldTransform();
	//getter和setter函数
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) {mPosition = pos; mRecomputeWorldTransform = true;}
	float GetScale()const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	const Quaternion& GetRotation()const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
	State GetState()const { return mState; }
	void SetState(State state) { mState = state; }

	//在构造函数中初始化该成员
	class Game* GetGame() { return mGame; }

	//添加或删除组件
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//actor的状态
	State mState;
	Matrix4 mWorldTransform;
	Vector3 mPosition;
	Quaternion mRotation;
	float mScale;
	bool mRecomputeWorldTransform;

	//管理附属在actor上的components
	std::vector<class Component*> mComponents;
	//通过依赖注入的方式（拥有Game类对象的指针），从而访问Game类对象
	class Game* mGame;
};
