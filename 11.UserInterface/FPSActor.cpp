#include "FPSActor.h"
#include "MoveComponent.h"
#include "SDL/SDL_scancode.h"
#include "Renderer.h"
#include "AudioSystem.h"
#include "Game.h"
#include "AudioComponent.h"
#include "MeshComponent.h"
#include "FPSCamera.h"
#include "Actor.h"
#include "BoxComponent.h"
#include "PlaneActor.h"
#include "Mesh.h"

FPSActor::FPSActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);

	mCameraComp = new FPSCamera(this);

	mFPSModel = new Actor(game);
	mFPSModel->SetScale(0.75f);
	mMeshComp = new MeshComponent(mFPSModel);
	mMeshComp->SetMesh(game->GetRenderer()->GetMesh("Assets/Rifle.gpmesh"));

	// Add a box component
	mBoxComp = new BoxComponent(this);
	AABB myBox(Vector3(-25.0f, -25.0f, -87.5f),
		Vector3(25.0f, 25.0f, 87.5f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);
}

void FPSActor::UpdateActor(float deltaTime)
{
	UpdateActor(deltaTime);

	FixCollisions();

	// Play the footstep if we're moving and haven't recently
	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) ||
		!Math::NearZero(mMoveComp->GetStrafeSpeed())) &&
		mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}

	// Update position of FPS model relative to actor position
	const Vector3 modelOffset(Vector3(10.0f, 10.0f, -10.0f));
	Vector3 modelPos = GetPosition();
	modelPos += GetForward() * modelOffset.x;
	modelPos += GetRight() * modelOffset.y;
	modelPos.z += modelOffset.z;
	mFPSModel->SetPosition(modelPos);
	// Initialize rotation to actor rotation
	Quaternion q = GetRotation();
	// Rotate by pitch from camera
	q = Quaternion::Concatenate(q, Quaternion(GetRight(), mCameraComp->GetPitch()));
	mFPSModel->SetRotation(q);
}

void FPSActor::ActorInput(const uint8_t* keys)
{
	//键盘移动
	float forwardSpeed = 0.f;
	float strafeSpeed = 0.f;
	if(keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	//鼠标移动
	//从SDL获取鼠标的相对移动
	int x, y;
	SDL_GetRelativeMouseState(&x, &y);
	//假设鼠标移动始终在-500到500间
	const int maxMouseSpeed = 500;
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		//转换到[-1.0, 1.0]
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		// Multiply by rotation/sec
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	// Compute pitch
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		// Convert to ~[-1.0, 1.0]
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCameraComp->SetPitchSpeed(pitchSpeed);
}

void FPSActor::SetFootstepSurface(float value)
{
}

void FPSActor::SetVisible(bool visible)
{
}

void FPSActor::FixCollisions()
{
}
