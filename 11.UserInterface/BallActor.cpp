#include "BallActor.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Game.h"
#include "BallMove.h"
#include "Renderer.h"
#include "AudioComponent.h"

BallActor::BallActor(Game* game)
	:Actor(game)
{
	//SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh");
	mc->SetMesh(mesh);
	mMyMove = new BallMove(this);
	mMyMove->SetForwardSpeed(1500.0f);
	mAudioComp = new AudioComponent(this);
}

void BallActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mLifeSpan -= deltaTime;
	if (mLifeSpan < 0.0f)
	{
		SetState(EDead);
	}
}

void BallActor::SetPlayer(Actor* player)
{
	mMyMove->SetPlayer(player);
}

void BallActor::HitTarget()
{
	mAudioComp->PlayEvent("event:/Ding");
}