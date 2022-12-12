#include "BallMove.h"
#include "Math.h"
#include "Actor.h"
#include "PhysWorld.h"

BallMove::BallMove(Actor* owner)
	:MoveComponent(owner)
{
}

void BallMove::Update(float deltaTime)
{
	// Construct segment in direction of travel
	const float segmentLength = 30.0f;
	Vector3 start = mOwner->GetPosition();
	Vector3 dir = mOwner->GetForward();
	Vector3 end = start + dir * segmentLength;

	// Test segment vs world
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
}
