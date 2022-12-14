#pragma once
#include "Actor.h"

class Ship :public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	//void ProcessKeyboard(const uint8_t* state);
	void ActorInput(const uint8_t* keyState) override;
	//float GetRightSpeed() const { return mRightSpeed; }
	//float GetDownSpeed() const { return mDownSpeed; }
private:
	//float mRightSpeed;
	//float mDownSpeed;
	float mLaserCooldown;
};