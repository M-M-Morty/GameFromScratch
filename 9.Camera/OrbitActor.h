#pragma once

#include "Actor.h"
#include "OrbitCamera.h"


class OrbitActor :public Actor 
{
private:
	class OrbitCamera* mCameraComp;
	class MeshComponent* mMeshComp;
public:
	OrbitActor(class Game* game);

	void ActorInput(const uint8_t* keys) override;

	void SetVisible(bool visible);
};