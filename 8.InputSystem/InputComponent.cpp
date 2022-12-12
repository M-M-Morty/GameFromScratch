#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner)
	:MoveComponent(owner)
	,mForwardKey(0)
	,mBackKey(0)
	,mClockwiseKey(0)
	,mCounterClockwiseKey(0)
{

}


void InputComponent::ProcessInput(const struct InputState& state)
{
	float forwardSpeed = 0.f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
