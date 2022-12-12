#pragma once
#include "Actor.h"

class BallActor :public Actor
{
private:
	class AudioComponent* mAudioComp;
	class BallMove* mMyMove;
	float mLifeSpan;
public:
	BallActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void SetPlayer(Actor* player);

	void HitTarget();
};